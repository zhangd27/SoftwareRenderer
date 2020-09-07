//
//  simpleShader.cpp
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/25.
//  Copyright © 2020 zhang. All rights reserved.
//

#include "simpleShader.h"


namespace SoftwareRenderer {

SimpleShader::SimpleShader() {
    texture = nullptr;
    modelMat = Mat4fIdentity;
    viewMat = Mat4fIdentity;
    projMat = Mat4fIdentity;
}

Vertex SimpleShader::vShader(const Vertex &vertexIn) {
    Vertex vertexOut;
    vertexOut.position = modelMat(vertexIn.position);
    vertexOut.posTrans = (projMat * viewMat)(vertexOut.position);    
    vertexOut.color = vertexIn.color;
    vertexOut.normal = vertexIn.normal;
    vertexOut.u = vertexIn.u;
    vertexOut.v = vertexIn.v;
    
    return vertexOut;
}

Color SimpleShader::fShader(const Vertex &vertexOut) {
    Color c = vertexOut.color;
    if (texture)
        c = texture->sampler(vertexOut.u, vertexOut.v);
    
    return c;
}

}
