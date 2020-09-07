//
//  canvas.cpp
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/17.
//  Copyright © 2020 zhang. All rights reserved.
//

#include <cstring>
#include "canvas.h"
#include "../math/transformation.h"
#include "../shaders/simpleShader.h"
#include "../shaders/BlinnPhongShader.h"


namespace SoftwareRenderer {

Canvas::Canvas(uint32_t *pixels, int _width, int _height): pixels(pixels) {
    setting.width = _width;
    setting.height = _height;
    setting.light = nullptr;
    setting.shader = nullptr;
    setting.backBuffer = nullptr;
    setting.frontBuffer = nullptr;
    setting.cameraPos = Vec3f(0.0f, 0.0f, 0.0f);
}

Canvas::~Canvas() {
    if (setting.light) delete setting.light;
    if (setting.shader) delete setting.shader;
    if (setting.backBuffer) delete setting.backBuffer;
    if (setting.frontBuffer) delete setting.frontBuffer;
    
    setting.light = nullptr;
    setting.shader = nullptr;
    setting.backBuffer = nullptr;
    setting.frontBuffer = nullptr;
    
    for (unsigned int i = 0; i < setting.meshes.size(); i++) {
        delete setting.meshes[i];
        setting.meshes[i] = nullptr;
    }
}

void Canvas::initialize() {
    if (setting.shader) delete setting.shader;
    if (setting.backBuffer) delete setting.backBuffer;
    if (setting.frontBuffer) delete setting.frontBuffer;
    if (setting.light) delete setting.light;
    
    setting.shader = new SimpleShader();
    setting.light = new Light();
    setting.backBuffer = new Framebuffer(setting.width, setting.height);
    setting.frontBuffer = new Framebuffer(setting.width, setting.height);
    setViewportMat(0, 0, setting.width, setting.height);
    defaultSetting();
}

void Canvas::setRenderingMode() {
    if (setting.renderMode == RenderMode::Fill)
        setting.renderMode = RenderMode::WireFrame;
    else setting.renderMode = RenderMode::Fill;
}

void Canvas::setShader(ShaderType shaderType) {
    if (setting.shader) delete setting.shader;
    setting.shader = nullptr;
    switch (shaderType) {
        case ShaderType::Simple:
            setting.shader = new SimpleShader();
            setting.shaderType = ShaderType::Simple;
            break;
        case ShaderType::BlinnPhong:
            setting.shader = new BlinnPhongShader();
            resetLight();
            setting.shader->setLight(setting.light);
            setting.shaderType = ShaderType::BlinnPhong;
            break;
        default:
            break;
    }
}

void Canvas::loadMesh(const char *path) {
    Mesh *mesh = new Mesh(path);
    setting.meshes.push_back(mesh);
}

void Canvas::loadMesh(const char *path, const char *texturePath) {
    Mesh *mesh = new Mesh(path, texturePath);
    setting.meshes.push_back(mesh);
}

void Canvas::bindTexture(const Mesh *mesh) {
    setting.shader->bindTexture(mesh->texture);
}

void Canvas::unBindTexture() {
    setting.shader->bindTexture(nullptr);
}

void Canvas::setModelMat(const Mat4f &rotation) {
    Vec3f target(0.0f);
    float scaleInv = 100000.0f;
    for (const auto &mesh : setting.meshes) {
        target += mesh->center;
        scaleInv = std::min(scaleInv, mesh->scaleInv);
    }
    target /= static_cast<float>(setting.meshes.size());
    auto translation = translate(target * -1.0f);
    auto scaler = scale(scaleInv, scaleInv, scaleInv);
    auto model = scaler * rotation * translation;
    setting.shader->setModelMat(model);
}

void Canvas::setViewMat(const Vec3f &cameraPos, const Vec3f &target, const Vec3f &worldUp) {
    setting.cameraPos = cameraPos;
    setting.shader->setCameraPos(cameraPos);
    setting.shader->setViewMat(lookat(cameraPos, target, worldUp));
}

void Canvas::setViewMat(const Vec3f &cameraPos, const Mat4f &mat) {
    setting.cameraPos = cameraPos;
    setting.shader->setCameraPos(cameraPos);
    setting.shader->setViewMat(mat);
}

void Canvas::setNearAndFar(float near, float far) {
    setting.near = near;
    setting.far = far;
}

void Canvas::setProjMat(float angle, float aspect) {
    setting.shader->setProjMat(perspective(angle, aspect, setting.near, setting.far));
}

void Canvas::setViewportMat(int left, int right, int width, int height) {
    setting.viewportMat = viewport_trans(left, right, width, height);
}

void Canvas::clearFramebuffer() {
    setting.backBuffer->clearBuffer();
}

void Canvas::swapFramebuffer() {
    Framebuffer *tmp = setting.frontBuffer;
    setting.frontBuffer = setting.backBuffer;
    setting.backBuffer = tmp;
}

void Canvas::defaultSetting() {
    setting.doDepthTesting = true;
    setting.doClipping = true;
    setting.doBackFaceCulling = false;
    setting.doAlphaBlend = false;
    setting.renderMode = RenderMode::Fill;
    setting.shaderType = ShaderType::Simple;
    setNearAndFar(0.1f, 100.0f);
}

// Bresenham's line algorithm
void Canvas::drawLine(const Vertex &v1, const Vertex &v2) {
    int x1 = v1.posTrans.x;
    int y1 = v1.posTrans.y;
    int x2 = v2.posTrans.x;
    int y2 = v2.posTrans.y;
    //Color c1 = v1.color;
    //Color c2 = v2.color;
    Color c(255);
    
    bool steep = false;
    if (std::abs(x1 - x2) < std::abs(y1 - y2)) {
        std::swap(x1, y1);
        std::swap(x2, y2);
        steep = true;
    }
    
    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
        //std::swap(c1, c2);
    }
    
    int delta_x = x2 - x1;
    int delta_y = y2 - y1;
    int derror = std::abs(delta_y) * 2;
    int error = 0;
    int y = y1;
 
    for (int x = x1; x <= x2; x++) {
        //Color c = c1 + ((c2 - c1) * ((float)(x - x1)/delta_x));
        if (steep)
            setting.backBuffer->setPixelColor(y, x, c);
        else
            setting.backBuffer->setPixelColor(x, y, c);
        
        error += derror;
        if (error > delta_x) {
            y += (y2 > y1 ? 1 : -1);
            error -= delta_x * 2;
        }
    }
}

// Triangle rasterization
// Barycentric algorithm
void Canvas::drawTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3) {
    float x1 = v1.posTrans.x;
    float y1 = v1.posTrans.y;
    float x2 = v2.posTrans.x;
    float y2 = v2.posTrans.y;
    float x3 = v3.posTrans.x;
    float y3 = v3.posTrans.y;

    float x_min = std::min(std::min(x1, x2), x3);
    float x_max = std::max(std::max(x1, x2), x3);
    float y_min = std::min(std::min(y1, y2), y3);
    float y_max = std::max(std::max(y1, y2), y3);
    
    for (int i = x_min; i < x_max; i++) {
        for (int j = y_min; j < y_max; j++) {
            float inv = 1 / ((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1));
            float fu = ((i - x1) * (y3 - y1) - (j - y1) * (x3 - x1)) * inv;
            float fv = ((j - y1) * (x2 - x1) - (i - x1) * (y2 - y1)) * inv;
            if (fu >= 0 && fv >= 0 && fu + fv <= 1.0f) {
                float z1 = v1.posTrans.z;
                float z2 = v2.posTrans.z;
                float z3 = v3.posTrans.z;
                float z = z1 * (1-fu-fv) + z2 * fu + z3 * fv;
                if (!setting.doAlphaBlend) {
                    if (z < setting.backBuffer->getDepth(i - 0.5f, j - 0.5f)) {
                        Vertex tmp;
                        // perspective correction
                        float factor = (setting.far + setting.near) / (setting.far - setting.near);
                        tmp.color = Color(); // not necessary
                        tmp.u = ((1 - fu - fv) * v1.u * (z1 - factor) + fu * v2.u * (z2 - factor) + fv * v3.u * (z3 - factor)) / (z - factor);
                        tmp.v = ((1 - fu - fv) * v1.v * (z1 - factor) + fu * v2.v * (z2 - factor) + fv * v3.v * (z3 - factor)) / (z - factor);
                        //tmp.color = v1.color * (1 - fu - fv) + v2.color * fu + v3.color * fv;
                        if (setting.shaderType == ShaderType::BlinnPhong) {
                            tmp.normal = (v1.normal * (1 - fu - fv) * (z1 - factor) + v2.normal * fu * (z2 - factor) + v3.normal * fv * (z3 - factor)) / (z - factor);
                        }
                        Color c = setting.shader->fShader(tmp);
                        setting.backBuffer->setPixelColor(i - 0.5f, j - 0.5f, c);
                        setting.backBuffer->setDepth(i - 0.5f, j - 0.5f, z);
                    }
                }
                else {
                    //
                }
            }
        }
    }
}

// draw mesh
/* ********************************
 Pipeline:
 For Each Mesh:
    1. Bind Texture
    2. Vertex Shader
    3. Viewport Transformation
    4. Rasterization
    5. Fragment Shader
    6. Unbind Texture
********************************* */
void Canvas::drawMesh() {
    for (const auto &mesh : setting.meshes) {
        bindTexture(mesh);
        for (unsigned int i = 0; i < mesh->indices.size(); i += 3) {            
            const Vertex &a = mesh->vertices[mesh->indices[i]];
            const Vertex &b = mesh->vertices[mesh->indices[i]+1];
            const Vertex &c = mesh->vertices[mesh->indices[i]+2];
        
            auto v1 = setting.shader->vShader(a);
            auto v2 = setting.shader->vShader(b);
            auto v3 = setting.shader->vShader(c);
            
            // back face culling
            if (setting.doBackFaceCulling && backFaceCulling(v1.position, v2.position, v3.position))
                continue;
            
            // clipping
            bool clipLine1 = false, clipLine2 = false, clipLine3 = false;
            if (setting.doClipping) {
                if (setting.renderMode == RenderMode::WireFrame) {
                    clipLine1 = lineClipping(v1, v2);
                    clipLine2 = lineClipping(v2, v3);
                    clipLine3 = lineClipping(v3, v1);
                }
                else if (setting.renderMode == RenderMode::Fill && triangleClipping(v1, v2, v3))
                    continue;
            }
            
            // viewport trans
            v1.posTrans = setting.viewportMat(v1.posTrans);
            v2.posTrans = setting.viewportMat(v2.posTrans);
            v3.posTrans = setting.viewportMat(v3.posTrans);
            // rasterize
            if (setting.renderMode == RenderMode::Fill)
                drawTriangle(v1, v2, v3);
            else if (setting.renderMode == RenderMode::WireFrame) {
                if (!clipLine1) drawLine(v1, v2);
                if (!clipLine2) drawLine(v2, v3);
                if (!clipLine3) drawLine(v3, v1);
            }
            
        }
        unBindTexture();
    }
}

// send color buffer
void Canvas::drawPixels() {
    swapFramebuffer();
    std::memcpy(pixels, setting.frontBuffer->getColorbuffer(), sizeof(uint32_t) * setting.width * setting.height);
}

bool Canvas::backFaceCulling(const Vec3f &pos1, const Vec3f &pos2, const Vec3f &pos3) {
    if (setting.renderMode == RenderMode::WireFrame)
        return false;
    auto tmp1 = pos2 - pos1;
    auto tmp2 = pos3 - pos1;
    auto viewRay = setting.cameraPos - pos1;
    auto normal = tmp1.cross(tmp2);
    
    return normal.dot(viewRay) < 0;
}

bool Canvas::lineClipping(const Vertex &v1, const Vertex &v2) {
    float vMin = -1.0f, vMax = 1.0f;
    float x1 = v1.posTrans.x, y1 = v1.posTrans.y;
    float x2 = v2.posTrans.x, y2 = v2.posTrans.y;
    
    int tmp = 0;
    int outcode1 = 0, outcode2 = 0;

    // outcode1 calculation.
    tmp = (y1>vMax)?1:0;
    tmp <<= 3;
    outcode1 |= tmp;
    tmp = (y1<vMin)?1:0;
    tmp <<= 2;
    outcode1 |= tmp;
    tmp = (x1>vMax)?1:0;
    tmp <<= 1;
    outcode1 |= tmp;
    tmp = (x1<vMin)?1:0;
    outcode1 |= tmp;

    // outcode2 calculation.
    tmp = (y2>vMax)?1:0;
    tmp <<= 3;
    outcode2 |= tmp;
    tmp = (y2<vMin)?1:0;
    tmp <<= 2;
    outcode2 |= tmp;
    tmp = (x2>vMax)?1:0;
    tmp <<= 1;
    outcode2 |= tmp;
    tmp = (x2<vMin)?1:0;
    outcode2 |= tmp;

    if((outcode1 & outcode2) != 0)
        return true;

    // bounding box judge.
    Vec2f minPoint,maxPoint;
    minPoint.x = std::min(v1.posTrans.x, v2.posTrans.x);
    minPoint.y = std::min(v1.posTrans.y, v2.posTrans.y);
    maxPoint.x = std::max(v1.posTrans.x, v2.posTrans.x);
    maxPoint.y = std::max(v1.posTrans.y, v2.posTrans.y);
    if(minPoint.x > vMax || maxPoint.x < vMin || minPoint.y > vMax || maxPoint.y < vMin)
        return true;

    return false;
}

bool Canvas::triangleClipping(const Vertex &v1, const Vertex &v2, const Vertex &v3) {
    float vMin = -1.0f;
    float vMax = 1.0f;
    
    // if the triangle is too far to see it, clip it
    if(v1.posTrans.z > vMax && v2.posTrans.z > vMax && v3.posTrans.z > vMax)
        return true;

    // if the triangle is behind the camera, clip it
    if(v1.posTrans.z < vMin && v2.posTrans.z < vMin && v3.posTrans.z < vMin)
        return true;

    // check if clip or not by simple AABB.
    Vec2f minPoint,maxPoint;
    minPoint.x = std::min(v1.posTrans.x, std::min(v2.posTrans.x, v3.posTrans.x));
    minPoint.y = std::min(v1.posTrans.y, std::min(v2.posTrans.y, v3.posTrans.y));
    maxPoint.x = std::max(v1.posTrans.x, std::max(v2.posTrans.x, v3.posTrans.x));
    maxPoint.y = std::max(v1.posTrans.y, std::max(v2.posTrans.y, v3.posTrans.y));
    if(minPoint.x > vMax || maxPoint.x < vMin || minPoint.y > vMax || maxPoint.y < vMin)
        return true;

    return false;
}

void Canvas::processKeyInput(float deltatime, KEYINPUT key) {
    if (setting.shaderType == ShaderType::BlinnPhong) {
        setting.light->processKeyInput(deltatime, key);
        setting.shader->setLight(setting.light);
    }
}

}
