//
//  BlinnPhongShader.h
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/29.
//  Copyright © 2020 zhang. All rights reserved.
//

#ifndef BlinnPhongShader_h
#define BlinnPhongShader_h

#include "shader.h"
#include "../math/transformation.h"


namespace SoftwareRenderer {

class BlinnPhongShader : public BasicShader {
    Mat4f modelMat;
    Mat4f viewMat;
    Mat4f projMat;
    Mat4f invModelMat;
    Vec3f cameraPos;
    Texture2D *texture;
    Light *light;
        
public:
    BlinnPhongShader();
    virtual ~BlinnPhongShader() = default;
    
    virtual Vertex vShader(const Vertex &vertexIn) override;
    virtual Color fShader(const Vertex &vertexOut) override;
    
    virtual void setModelMat(const Mat4f &model) override {modelMat = model; invModelMat = inverse(modelMat);}
    virtual void setViewMat(const Mat4f &view) override {viewMat = view;}
    virtual void setProjMat(const Mat4f &proj) override {projMat = proj;}
    
    virtual void setCameraPos(const Vec3f &cameraPos_) override {cameraPos = cameraPos_;}
    virtual void bindTexture(Texture2D *text) override {texture = text;}
        
    virtual void setLight(Light *light_) override {light = light_;}
    virtual void setMaterial(Material *material) override{}
};

}

#endif /* BlinnPhongShader_h */
