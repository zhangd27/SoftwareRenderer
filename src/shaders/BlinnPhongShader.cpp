//
//  BlinnPhongShader.cpp
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/29.
//  Copyright © 2020 zhang. All rights reserved.
//

#include "BlinnPhongShader.h"


namespace SoftwareRenderer {

BlinnPhongShader::BlinnPhongShader() {
    texture = nullptr;
    light = nullptr;
    modelMat = Mat4fIdentity;
    viewMat = Mat4fIdentity;
    projMat = Mat4fIdentity;
    invModelMat = Mat4fIdentity;
}

Vertex BlinnPhongShader::vShader(const Vertex &vertexIn) {
    Vertex vertexOut;
    vertexOut.position = modelMat(vertexIn.position);
    vertexOut.posTrans = (projMat * viewMat)(vertexOut.position);
    vertexOut.color = vertexIn.color;
    vertexOut.normal = invModelMat(vertexIn.normal, false);
    vertexOut.u = vertexIn.u;
    vertexOut.v = vertexIn.v;
    
    return vertexOut;
}

Color BlinnPhongShader::fShader(const Vertex &vertexOut) {
    Color c = vertexOut.color;
    if (texture)
        c = texture->sampler(vertexOut.u, vertexOut.v);
    
    Vec3f color(c.x, c.y, c.z);
    
    auto globalLight = color * 0.2;
    
    // ambient
    auto ambient = color.multiply(light->ambient);
    
    // diffuse
    auto lightDir = (light->position - vertexOut.position).normalize();
    auto normal = vertexOut.normal.normalize();
    float diff = std::max(normal.dot(lightDir), 0.0f);
    auto diffuse = color.multiply(light->diffuse) * diff;
    
    // specular
    auto viewDir = (cameraPos - vertexOut.position).normalize();
    auto halfwayDir = (lightDir + viewDir).normalize();
    float spec = std::pow(std::max(normal.dot(halfwayDir), 0.0f), 50.0f);
    auto specular = color.multiply(light->specular) * spec;
    
    // attenuation
    float distance = (light->position - vertexOut.position).length();
    float attenuation = 1.0f / light->attenuation.dot(Vec3f(1.0f, distance, distance * distance));
    
    return Color((ambient + diffuse + specular) * attenuation + globalLight);
}

}
