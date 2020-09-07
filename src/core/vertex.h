//
//  vertex.h
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/20.
//  Copyright © 2020 zhang. All rights reserved.
//

#ifndef vertex_h
#define vertex_h

#include "../math/vector.h"
#include "color.h"


namespace SoftwareRenderer {

class Vertex {
public:
    Vec3f position;
    Vec3f normal;
    Color color;
    Vec3f posTrans;
    float u;
    float v;
    
    Vertex() = default;
    Vertex(const Vec3f &position, const Vec3f &normal, float u, float v, const Color &color = Color()) :
        position(position), normal(normal), color(color), u(u), v(v), posTrans(position) {}
    
};

}

#endif /* vertex_h */
