//
//  mesh.h
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/21.
//  Copyright © 2020 zhang. All rights reserved.
//

#ifndef mesh_h
#define mesh_h

#include <vector>

#include "texture.h"
#include "../core/vertex.h"


namespace SoftwareRenderer {

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Texture2D *texture;
    
    Vec3f minPoint;
    Vec3f maxPoint;
    Vec3f center;
    float scaleInv;
    //static const Mesh Cube;
    
    Mesh(const Mesh& mesh);
    Mesh(const char *path);
    Mesh(const char *path, const char *texturePath);
    ~Mesh();
    
private:
    void loadOBJ(const char *path);
};

}

#endif /* mesh_h */
