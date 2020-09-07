//
//  simpleShader.h
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/25.
//  Copyright © 2020 zhang. All rights reserved.
//

#ifndef simpleShader_h
#define simpleShader_h

#include "shader.h"


namespace SoftwareRenderer {

class SimpleShader : public BasicShader {
    Mat4f modelMat;
    Mat4f viewMat;
    Mat4f projMat;
    Texture2D *texture;
    
public:
    SimpleShader();
    virtual ~SimpleShader() = default;
    
    virtual Vertex vShader(const Vertex &vertexIn) override;
    virtual Color fShader(const Vertex &vertexOut) override;
    
    virtual void setModelMat(const Mat4f &model) override {modelMat = model;}
    virtual void setViewMat(const Mat4f &view) override {viewMat = view;}
    virtual void setProjMat(const Mat4f &proj) override {projMat = proj;}
    
    virtual void setCameraPos(const Vec3f &cameraPos) override {}
    virtual void bindTexture(Texture2D *text) override {texture = text;}
    
    virtual void setLight(Light *light) override {}
    virtual void setMaterial(Material *material) override{}
};

}

#endif /* simpleShader_h */
