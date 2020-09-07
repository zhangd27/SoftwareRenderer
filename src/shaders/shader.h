//
//  shader.h
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/21.
//  Copyright © 2020 zhang. All rights reserved.
//

#ifndef shader_h
#define shader_h

#include "../math/matrix.h"
#include "../core/vertex.h"
#include "../core/texture.h"
#include "../core/light.h"
#include "../core/material.h"


namespace SoftwareRenderer {

class BasicShader {

public:
    BasicShader() = default;
    virtual ~BasicShader() {};
    
    virtual Vertex vShader(const Vertex &vertexIn) = 0;
    virtual Color fShader(const Vertex &vertexOut) = 0;
    
    virtual void setModelMat(const Mat4f &model) = 0;
    virtual void setViewMat(const Mat4f &view) = 0;
    virtual void setProjMat(const Mat4f &proj) = 0;
    
    virtual void setCameraPos(const Vec3f &cameraPos) = 0;
    virtual void bindTexture(Texture2D *text) = 0;
    
    virtual void setLight(Light *light) = 0;
    virtual void setMaterial(Material *material) = 0;
};

}

#endif /* shader_h */
