//
//  orbitCamera.cpp
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/22.
//  Copyright © 2020 zhang. All rights reserved.
//

#include "orbitCamera.h"
#include "../math/constants.h"

namespace SoftwareRenderer {

OrbitCamera::OrbitCamera() {
    init();
}

Mat4f OrbitCamera::getViewMatrix() {
    return lookat(Position, Target, LocalUp);
}

Vec3f OrbitCamera::getPosition() {
    return Position;
}

Vec3f OrbitCamera::getTarget() {
    return Target;
}

void OrbitCamera::reset() {
    init();
}

void OrbitCamera::processMouseScroll(float yoffset) {
    radius *= std::pow(0.95, yoffset);
    radius = std::min(30.0f, std::max(radius, 2.0f));
    update();
}

void OrbitCamera::processMouseMovement(float xoffset, float yoffset, MOUSEBUTTONDOWN which) {
    if (which == MOUSEBUTTONDOWN::LEFT) {
        float factor = PI * 2;
        theta += MouseSense * xoffset * factor;
        phi += MouseSense * yoffset * factor;
        phi = std::max(EPISION, std::min(PI - EPISION, phi));
        update();
    }
    else {
        xoffset *= MouseSense;
        yoffset *= MouseSense;
        
        Vec3f forward = (Target - Position).normalize();
        Vec3f left = LocalUp.cross(forward);
        Vec3f up = forward.cross(left);
        Vec3f trueX = left * xoffset;
        Vec3f trueY = up * yoffset;
        Position -= trueX + trueY;
        Target -= trueX + trueY;
    }
}

void OrbitCamera::update() {
    Vec3f offset;
    offset.x = radius * std::sin(phi) * std::sin(theta);
    offset.y = radius * std::cos(phi);
    offset.z = radius * std::sin(phi) * std::cos(theta);
    Position = Target + offset;
}

void OrbitCamera::init() {
    Position = Vec3f(0.0f, 0.0f, 3.0f);
    Target = Vec3f(0.0f, 0.0f, 0.0f);
    theta = 0.0f;
    phi = PI / 2.0f;
    radius = 3.0f;
}

}
