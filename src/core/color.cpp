//
//  color.cpp
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/19.
//  Copyright © 2020 zhang. All rights reserved.
//

#include "color.h"


namespace SoftwareRenderer {

Color::Color() : Vec4f(0.0f, 0.0f, 0.0f, 255.0f) {}
Color::Color(float t) {
    float rgb = t < 255.0f ? t : 255.0f;
    x = y = z = rgb;
    w = 255.0f;
}//: Vec4f(t, t, t, 255.0f) {}
Color::Color(float r, float g, float b, float a){
    x = r < 255.0f ? r : 255.0f;
    y = g < 255.0f ? g : 255.0f;
    z = b < 255.0f ? b : 255.0f;
    w = a < 255.0f ? a : 255.0f;
}//: Vec4f(r, g, b, a) {}
Color::Color(const Vec4f &vec) {
    x = std::min(255.0f, vec.x);
    y = std::min(255.0f, vec.y);
    z = std::min(255.0f, vec.z);
    w = std::min(255.0f, vec.w);
}//: Vec4f(vec) {}
Color::Color(const Vec3f &vec, float a) {
    w = std::min(255.0f, a);
    x = std::min(255.0f, vec.x);
    y = std::min(255.0f, vec.y);
    z = std::min(255.0f, vec.z);
}//: Vec4f(vec, a) {}

uint32_t Color::uint32() const {
    uint32_t R = static_cast<uint32_t>(x);
    uint32_t G = static_cast<uint32_t>(y);
    uint32_t B = static_cast<uint32_t>(z);
    uint32_t A = static_cast<uint32_t>(w);

    uint32_t value = (A << 24) | (R << 16) | (G << 8) | B;

    return value;
}

}
