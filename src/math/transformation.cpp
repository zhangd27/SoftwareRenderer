//
//  transformation.cpp
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/20.
//  Copyright © 2020 zhang. All rights reserved.
//

#include "transformation.h"


namespace SoftwareRenderer {

Mat4f inverse(const Mat4f &m) {
    float inv[16];
    
    inv[0] = m._m[5] * m._m[10] * m._m[15] -
                    m._m[5]  * m._m[11] * m._m[14] -
                    m._m[9]  * m._m[6]  * m._m[15] +
                    m._m[9]  * m._m[7]  * m._m[14] +
                    m._m[13] * m._m[6]  * m._m[11] -
                    m._m[13] * m._m[7]  * m._m[10];

    inv[4] = -m._m[4] * m._m[10] * m._m[15] +
                    m._m[4]  * m._m[11] * m._m[14] +
                    m._m[8]  * m._m[6]  * m._m[15] -
                    m._m[8]  * m._m[7]  * m._m[14] -
                    m._m[12] * m._m[6]  * m._m[11] +
                    m._m[12] * m._m[7]  * m._m[10];

    inv[8] = m._m[4]  * m._m[9]  * m._m[15] -
                    m._m[4]  * m._m[11] * m._m[13] -
                    m._m[8]  * m._m[5]  * m._m[15] +
                    m._m[8]  * m._m[7]  * m._m[13] +
                    m._m[12] * m._m[5]  * m._m[11] -
                    m._m[12] * m._m[7]  * m._m[9];

    inv[12] = -m._m[4]  * m._m[9]  * m._m[14] +
                    m._m[4]  * m._m[10] * m._m[13] +
                    m._m[8]  * m._m[5]  * m._m[14] -
                    m._m[8]  * m._m[6]  * m._m[13] -
                    m._m[12] * m._m[5]  * m._m[10] +
                    m._m[12] * m._m[6]  * m._m[9];

    inv[1] = -m._m[1]  * m._m[10] * m._m[15] +
                    m._m[1]  * m._m[11] * m._m[14] +
                    m._m[9]  * m._m[2] *  m._m[15] -
                    m._m[9]  * m._m[3] *  m._m[14] -
                    m._m[13] * m._m[2] *  m._m[11] +
                    m._m[13] * m._m[3] *  m._m[10];

    inv[5] =  m._m[0]  * m._m[10] * m._m[15] -
                    m._m[0]  * m._m[11] * m._m[14] -
                    m._m[8]  * m._m[2]  * m._m[15] +
                    m._m[8]  * m._m[3]  * m._m[14] +
                    m._m[12] * m._m[2]  * m._m[11] -
                    m._m[12] * m._m[3]  * m._m[10];

    inv[9] = -m._m[0]  * m._m[9]  * m._m[15] +
                    m._m[0]  * m._m[11] * m._m[13] +
                    m._m[8]  * m._m[1]  * m._m[15] -
                    m._m[8]  * m._m[3]  * m._m[13] -
                    m._m[12] * m._m[1]  * m._m[11] +
                    m._m[12] * m._m[3]  * m._m[9];

    inv[13] = m._m[0]  * m._m[9]  * m._m[14] -
                    m._m[0]  * m._m[10] * m._m[13] -
                    m._m[8]  * m._m[1]  * m._m[14] +
                    m._m[8]  * m._m[2]  * m._m[13] +
                    m._m[12] * m._m[1]  * m._m[10] -
                    m._m[12] * m._m[2]  * m._m[9];

    inv[2] = m._m[1]  * m._m[6] * m._m[15] -
                    m._m[1]  * m._m[7] * m._m[14] -
                    m._m[5]  * m._m[2] * m._m[15] +
                    m._m[5]  * m._m[3] * m._m[14] +
                    m._m[13] * m._m[2] * m._m[7] -
                    m._m[13] * m._m[3] * m._m[6];

    inv[6] = -m._m[0]  * m._m[6] * m._m[15] +
                    m._m[0]  * m._m[7] * m._m[14] +
                    m._m[4]  * m._m[2] * m._m[15] -
                    m._m[4]  * m._m[3] * m._m[14] -
                    m._m[12] * m._m[2] * m._m[7] +
                    m._m[12] * m._m[3] * m._m[6];

    inv[10] = m._m[0]  * m._m[5] * m._m[15] -
                    m._m[0]  * m._m[7] * m._m[13] -
                    m._m[4]  * m._m[1] * m._m[15] +
                    m._m[4]  * m._m[3] * m._m[13] +
                    m._m[12] * m._m[1] * m._m[7] -
                    m._m[12] * m._m[3] * m._m[5];

    inv[14] = -m._m[0]  * m._m[5] * m._m[14] +
                    m._m[0]  * m._m[6] * m._m[13] +
                    m._m[4]  * m._m[1] * m._m[14] -
                    m._m[4]  * m._m[2] * m._m[13] -
                    m._m[12] * m._m[1] * m._m[6] +
                    m._m[12] * m._m[2] * m._m[5];

    inv[3] = -m._m[1] * m._m[6] * m._m[11] +
                    m._m[1] * m._m[7] * m._m[10] +
                    m._m[5] * m._m[2] * m._m[11] -
                    m._m[5] * m._m[3] * m._m[10] -
                    m._m[9] * m._m[2] * m._m[7] +
                    m._m[9] * m._m[3] * m._m[6];

    inv[7] =  m._m[0] * m._m[6] * m._m[11] -
                    m._m[0] * m._m[7] * m._m[10] -
                    m._m[4] * m._m[2] * m._m[11] +
                    m._m[4] * m._m[3] * m._m[10] +
                    m._m[8] * m._m[2] * m._m[7] -
                    m._m[8] * m._m[3] * m._m[6];

    inv[11] = -m._m[0] * m._m[5] * m._m[11] +
                    m._m[0] * m._m[7] * m._m[9] +
                    m._m[4] * m._m[1] * m._m[11] -
                    m._m[4] * m._m[3] * m._m[9] -
                    m._m[8] * m._m[1] * m._m[7] +
                    m._m[8] * m._m[3] * m._m[5];

    inv[15] = m._m[0] * m._m[5] * m._m[10] -
                    m._m[0] * m._m[6] * m._m[9] -
                    m._m[4] * m._m[1] * m._m[10] +
                    m._m[4] * m._m[2] * m._m[9] +
                    m._m[8] * m._m[1] * m._m[6] -
                    m._m[8] * m._m[2] * m._m[5];

    float det = m._m[0] * inv[0] + m._m[1] * inv[4] + m._m[2] * inv[8] + m._m[3] * inv[12];

    if (det == 0) return Mat4fIdentity;

    Mat4f ret;
    det = 1.0 / det;
    for (int i = 0; i < 16; ++i)
        ret._m[i] = inv[i] * det;
    return ret;
}

Mat4f translate(const Vec3f &v) {
    return Mat4f(1.0f, 0.0f, 0.0f, v.x, 0.0f, 1.0f, 0.0f, v.y, 0.0f, 0.0f, 1.0f, v.z, 0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4f scale(const float x, const float y, const float z) {
    return Mat4f(x, 0.0f, 0.0f, 0.0f, 0.0f, y, 0.0f, 0.0f, 0.0f, 0.0f, z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4f euler_rotate(const float angle, const Vec3f &v) {
    Vec3f norm = v.normalize();
    float c = std::cos(radian(angle));
    float s = std::sin(radian(angle));
    float xy = norm.x * norm.y;
    float xz = norm.x * norm.z;
    float yz = norm.y * norm.z;
    float xx = norm.x * norm.x;
    float yy = norm.y * norm.y;
    float zz = norm.z * norm.z;
    return Mat4f(c+xx*(1-c), xy*(1-c)-norm.z*s, xz*(1-c)+norm.y*s, 0.0f,
                 xy*(1-c)+norm.z*s, c+yy*(1-c), yz*(1-c)-norm.x*s, 0.0f,
                 xz*(1-c)-norm.y*s, yz*(1-c)+norm.x*s, c+zz*(1-c), 0.0f,
                 0.0f, 0.0f, 0.0f, 1.0f);
}


Mat4f ortho(const float left, const float right , const float bottom, const float top, const float near, const float far) {
    return Mat4f(2.0f/(right-left), 0.0f, 0.0f, (right+left)/(left-right),
                 0.0f, 2.0f/(top-bottom), 0.0f, (top+bottom)/(bottom-top),
                 0.0f, 0.0f, 2.0f/(near-far), (near+far)/(near-far),
                 0.0f, 0.0f, 0.0f, 1.0f);
}


Mat4f perspective(const float angle, const float aspect, const float near, const float far) {
    float fov = 1.0f / std::tan(radian(angle) * 0.5f);
    return Mat4f(fov/aspect, 0.0f, 0.0f, 0.0f,
                 0.0f, fov, 0.0f, 0.0f,
                 0.0f, 0.0f, (far+near)/(near-far), 2*far*near/(near-far),
                 0.0f, 0.0f, -1.0f, 0.0f);
}

Mat4f lookat(const Vec3f &cameraPos, const Vec3f &target, const Vec3f &worldUp) {
    Mat4f res = Mat4fIdentity;
    Vec3f zAxis = (cameraPos - target).normalize();
    Vec3f xAxis = worldUp.cross(zAxis).normalize();
    Vec3f yAxis = zAxis.cross(xAxis).normalize();
    
    res.m_[0][0] = xAxis.x;
    res.m_[0][1] = xAxis.y;
    res.m_[0][2] = xAxis.z;
    
    res.m_[1][0] = yAxis.x;
    res.m_[1][1] = yAxis.y;
    res.m_[1][2] = yAxis.z;
    
    res.m_[2][0] = zAxis.x;
    res.m_[2][1] = zAxis.y;
    res.m_[2][2] = zAxis.z;
    
    res.m_[0][3] = -(xAxis.dot(cameraPos));
    res.m_[1][3] = -(yAxis.dot(cameraPos));
    res.m_[2][3] = -(zAxis.dot(cameraPos));
    
    return res;
}

Mat4f viewport_trans(const int x, const int y, const int width, const int height) {
    Mat4f res = Mat4fIdentity;
    res.m_[0][0] = static_cast<float>(width) / 2.0f;
    res.m_[1][1] = -static_cast<float>(height) / 2.0f;
    res.m_[0][3] = static_cast<float>(x)+static_cast<float>(width-1)/2.0f;;
    res.m_[1][3] = static_cast<float>(y)+static_cast<float>(height-1)/2.0f;
    
    return res;
}

}
