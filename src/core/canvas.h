//
//  canvas.h
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/17.
//  Copyright © 2020 zhang. All rights reserved.
//

#ifndef canvas_h
#define canvas_h

#include <vector>

#include "framebuffer.h"
#include "mesh.h"
#include "light.h"
#include "../shaders/shader.h"


namespace SoftwareRenderer {

enum class RenderMode {
    WireFrame = 0,
    Fill = 1
};

enum class ShaderType {
    Simple = 0,
    BlinnPhong = 1
};

class Canvas {
    class Setting {
    public:
        bool doDepthTesting;
        bool doBackFaceCulling;
        bool doClipping;
        bool doAlphaBlend;
        RenderMode renderMode;
        ShaderType shaderType;
        
        int width, height;
        float near, far;
        
        BasicShader *shader;
        Light *light;
        std::vector<Mesh*> meshes;
        Material *material;
 
        // double buffer
        Framebuffer *backBuffer;
        Framebuffer *frontBuffer;
                
        Mat4f viewportMat;
        Vec3f cameraPos;
    };
    
    Setting setting;
    
public:
    Canvas(uint32_t *pixels, int _width, int _height);
    ~Canvas();
    
    void initialize();
    
    void setDepthTesting() {setting.doDepthTesting = !setting.doDepthTesting;}
    void setBackFaceCulling() {setting.doBackFaceCulling = !setting.doBackFaceCulling;}
    void setClipping() {setting.doClipping = !setting.doClipping;}
    void setRenderingMode();
    void setShader(ShaderType shaderType);
    
    // load mesh
    void loadMesh(const char *path);
    void loadMesh(const char *path, const char *texturePath);
    
    // bind texture
    void bindTexture(const Mesh *mesh);
    void unBindTexture();
    
    // set transform matrix
    void setModelMat(const Mat4f &rotation);
    void setViewMat(const Vec3f &cameraPos, const Mat4f &mat);
    void setViewMat(const Vec3f &cameraPos, const Vec3f &target, const Vec3f &worldUp);
    void setNearAndFar(float near, float far);
    void setProjMat(float angle, float aspect);
    void setViewportMat(int left, int right, int width, int height);
    
    // light setting
    void resetLight() {setting.light->reset();}
    
    // buffer operation
    void clearFramebuffer();
    void swapFramebuffer();
        
    // rasterization algorithm
    void drawLine(const Vertex &v1, const Vertex &v2);
    void drawTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3);
    
    // draw obj and set pixel color
    void drawMesh();
    void drawPixels();
    
    //process input
    void processKeyInput(float deltatime, KEYINPUT key);

private:
    uint32_t *pixels;
    
private:
    void defaultSetting();
    
    bool backFaceCulling(const Vec3f &pos1, const Vec3f &pos2, const Vec3f &pos3);
    bool lineClipping(const Vertex &v1, const Vertex &v2);
    bool triangleClipping(const Vertex &v1, const Vertex &v2, const Vertex &v3);
};

}

#endif /* canvas_h */
