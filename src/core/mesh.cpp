//
//  mesh.cpp
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/21.
//  Copyright © 2020 zhang. All rights reserved.
//

#include <fstream>
#include <sstream>

#include "mesh.h"


namespace SoftwareRenderer {

Mesh::Mesh(const Mesh &mesh): vertices(mesh.vertices), indices(mesh.indices), texture(mesh.texture),
minPoint(mesh.minPoint), maxPoint(mesh.maxPoint), center(mesh.center), scaleInv(mesh.scaleInv) { }

Mesh::Mesh(const char *path) {
    loadOBJ(path);
    texture = nullptr;
}

Mesh::Mesh(const char *path, const char *texturePath) {
    loadOBJ(path);
    texture = new Texture2D();
    texture->readImage(texturePath);
}

Mesh::~Mesh() {
    delete texture;       
    texture = nullptr;
}

void Mesh::loadOBJ(const char *path) {
    std::ifstream in;
    in.open(path, std::ifstream::in);
    if (in.fail())
        std::cout << "FAIL TO LOAD .OBJ" << std::endl;
    
    std::string line;
    std::vector<Vec3f> vs; // position
    std::vector<Vec3f> ns; // normal
    std::vector<Vec2f> ts; // texcoord
    minPoint = Vec3f(1000000, 1000000, 1000000);
    maxPoint = Vec3f(-1000000, -1000000, -1000000);
    
    while(!in.eof()) {
        getline(in, line);
        std::istringstream iss(line.c_str());
        char spam;
        // v
        if (!line.compare(0, 2, "v ")) {
            iss >> spam;
            Vec3f v;
            iss >> v.x;
            iss >> v.y;
            iss >> v.z;
            vs.push_back(v);
            if (minPoint.x > v.x) minPoint.x = v.x;
            if (minPoint.y > v.y) minPoint.y = v.y;
            if (minPoint.z > v.z) minPoint.z = v.z;
            if (maxPoint.x < v.x) maxPoint.x = v.x;
            if (maxPoint.y < v.y) maxPoint.y = v.y;
            if (maxPoint.z < v.z) maxPoint.z = v.z;
        }
        // vn
        else if (!line.compare(0, 3, "vn ")) {
            iss >> spam >> spam;
            Vec3f n;
            iss >> n.x;
            iss >> n.y;
            iss >> n.z;
            ns.push_back(n.normalize());
        }
        // vt
        else if (!line.compare(0, 3, "vt ")) {
            iss >> spam >> spam;
            Vec2f uv;
            iss >> uv.x;
            iss >> uv.y;
            ts.push_back(uv);
        }
        // f
        else if (!line.compare(0, 2, "f ")) {
            iss >> spam;
            int index[3];
            while (iss >> index[0] >> spam >> index[1] >> spam >> index[2]) {
                Vertex vData;
                vData.position = vData.posTrans = vs[index[0]-1];
                vData.normal = ns[index[2]-1];
                vData.u = ts[index[1]-1].x;
                vData.v = ts[index[1]-1].y;
                vData.color = Color(255);
                
                indices.push_back((unsigned int)vertices.size());
                vertices.push_back(vData);
            }
        }
        // ....
    }
    in.close();
    
    center = (minPoint + maxPoint) / 2.f;
    auto tmp = maxPoint - minPoint;
    float scale = std::max(tmp.x, tmp.y);
    scaleInv = 1 / scale;
}

}
