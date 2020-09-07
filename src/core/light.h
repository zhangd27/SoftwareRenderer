//
//  light.h
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/25.
//  Copyright © 2020 zhang. All rights reserved.
//

#ifndef light_h
#define light_h

#include "../math/vector.h"


namespace SoftwareRenderer {

enum class KEYINPUT {
    W = 0,
    S = 1,
    A = 2,
    D = 3
};

class Light { // This is a point light
public:
    // light attribute
    Vec3f ambient;
    Vec3f diffuse;
    Vec3f specular;
    Vec3f position;
    Vec3f attenuation;
    
    Light();
    ~Light() = default;
    
    void reset();
    void processKeyInput(float deltaTime, KEYINPUT key);
    void setLight(Vec3f ambient_, Vec3f diffuse_, Vec3f specular_, Vec3f position_, Vec3f attenuation_);
private:
    float moveSpeed;
};

}

#endif /* light_h */
