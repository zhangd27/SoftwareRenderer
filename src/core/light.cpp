//
//  light.cpp
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/25.
//  Copyright © 2020 zhang. All rights reserved.
//

#include "light.h"
#include "../math/transformation.h"
#include "../math/constants.h"

namespace SoftwareRenderer {

Light::Light() {
    reset();
    moveSpeed = 2.0f;
}

void Light::reset() {
    position = Vec3f(0.0f, 1.0f, 1.0f);
    ambient = Vec3f(0.2f);
    diffuse = Vec3f(0.5f);
    specular = Vec3f(0.5f);
    attenuation = Vec3f(1.0f, 0.045f, 0.0075f);
}

void Light::processKeyInput(float deltaTime, KEYINPUT key) {
    float velocity = deltaTime * moveSpeed;
    float factor = PI * 2;
    float distance = position.length();
    float theta = std::atan2(position.x, position.z);
    float phi = std::acos(position.y / distance);
    
    if (key == KEYINPUT::W) {
        phi -= velocity * factor;
        phi = std::max(EPISION, std::min(PI - EPISION, phi));
    }
    else if (key == KEYINPUT::S) {
        phi += velocity * factor;
        phi = std::max(EPISION, std::min(PI - EPISION, phi));
    }
    else if (key == KEYINPUT::A) {
        theta -= velocity * factor;
    }
    else {
        theta += velocity * factor;
    }
    
    position.x = distance * std::sin(phi) * std::sin(theta);
    position.y = distance * std::cos(phi);
    position.z = distance * std::sin(phi) * std::cos(theta);
}

void Light::setLight(Vec3f ambient_, Vec3f diffuse_, Vec3f specular_, Vec3f position_, Vec3f attenuation_) {
    ambient = ambient_;
    diffuse = diffuse_;
    specular = specular_;
    position = position_;
    attenuation = attenuation_;
}

}
