//
//  matrix.h
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/20.
//  Copyright © 2020 zhang. All rights reserved.
//

#ifndef matrix_h
#define matrix_h

#include <cstring>
#include "vector.h"


namespace SoftwareRenderer {

template <typename T>
class Mat4 {
public:
    union {
        T m_[4][4];
        T _m[16];
    };
        
    Mat4() = default;
    Mat4(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13,
         T m20, T m21, T m22, T m23, T m30, T m31, T m32, T m33) {
        m_[0][0] = m00, m_[1][0] = m10, m_[2][0] = m20, m_[3][0] = m30; // column
        m_[0][1] = m01, m_[1][1] = m11, m_[2][1] = m21, m_[3][1] = m31;
        m_[0][2] = m02, m_[1][2] = m12, m_[2][2] = m22, m_[3][2] = m32;
        m_[0][3] = m03, m_[1][3] = m13, m_[2][3] = m23, m_[3][3] = m33;
    }
    Mat4(const Mat4<T> &mat) {
        std::memcpy(this->m_, mat.m_, 16 * sizeof(T));
    }
    
    Mat4<T>& operator=(const Mat4<T> &mat) {
        std::memcpy(this->m_, mat.m_, 16 * sizeof(T));
        return *this;
    }
    
    bool operator==(const Mat4<T> &mat) const {
        return std::memcmp(m_, mat.m_, 16 * sizeof(T)) == 0;
    }
    bool operator!=(const Mat4<T> &mat) const {
        return !operator==(mat);
    }
    
    Mat4<T>  operator*(const Mat4<T> &mat) const {
        Mat4<T> res;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                res.m_[j][i] = m_[j][0] * mat.m_[0][i] + m_[j][1] * mat.m_[1][i] + m_[j][2] * mat.m_[2][i] + m_[j][3] * mat.m_[3][i];
        
        return res;
    }
    Mat4<T>& operator*=(const Mat4<T> &mat) {return *this = operator*(mat);}
    
    friend std::ostream& operator<<(std::ostream &os, const Mat4<T> &mat) {
        os << "4*4 Matrix:\n";
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                os << mat.m_[i][j] << " ";
            os << std::endl;
        }

        return os;
    }
    
    inline Vec3<T> operator()(const Vec3<T> &v, const bool isPoint = true) const {
        T x, y, z;
        if (isPoint) {
            x = m_[0][0] * v.x + m_[0][1] * v.y + m_[0][2] * v.z + m_[0][3];
            y = m_[1][0] * v.x + m_[1][1] * v.y + m_[1][2] * v.z + m_[1][3];
            z = m_[2][0] * v.x + m_[2][1] * v.y + m_[2][2] * v.z + m_[2][3];
            float w = m_[3][0] * v.x + m_[3][1] * v.y + m_[3][2] * v.z + m_[3][3];
        
            assert(w > 0);
            if (w != 1) {
                float invW = 1.0 / w;
                x *= invW;
                y *= invW;
                z *= invW;
            }
        }
        else {
            x = m_[0][0] * v.x + m_[0][1] * v.y + m_[0][2] * v.z;
            y = m_[1][0] * v.x + m_[1][1] * v.y + m_[1][2] * v.z;
            z = m_[2][0] * v.x + m_[2][1] * v.y + m_[2][2] * v.z;
        }
        return Vec3<T>(x, y, z);
    }
    
    Mat4<T> transpose() const {
        Mat4<T> res;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                res.m_[i][j] = m_[j][i];
        }
        return res;
    }
};

typedef Mat4<float> Mat4f;
typedef Mat4<int> Mat4i;
typedef Mat4<double> Mat4d;

static const Mat4<float> Mat4fIdentity{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};

}

#endif /* matrix_h */
