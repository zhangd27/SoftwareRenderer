//
//  vector.h
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/17.
//  Copyright © 2020 zhang. All rights reserved.
//

#ifndef vector_h
#define vector_h

#include <iostream>
#include <cmath>
#include <cassert>


namespace SoftwareRenderer {

template <typename T>
class Vec2 {
public:
    T x, y;
    
    // constructor
    Vec2(): x(0), y(0) {}
    Vec2(const T &t):x(t), y(t) {}
    Vec2(const T &x, const T &y): x(x), y(y) {}
    Vec2(const Vec2<T> &vec): x(vec.x), y(vec.y) {}

    // operator
    Vec2<T> operator+(const Vec2<T> &vec) const {
        return Vec2<T>(x + vec.x, y + vec.y);
    }
    Vec2<T> operator-(const Vec2<T> &vec) const {
        return Vec2<T>(x - vec.x, y - vec.y);
    }
    Vec2<T>& operator+=(const Vec2<T> &vec) {
        x += vec.x;
        y += vec.y;
        return *this;
    }
    Vec2<T>& operator-=(const Vec2<T> &vec) {
        x -= vec.x;
        y -= vec.y;
        return *this;
    }
    Vec2<T>& operator=(const Vec2<T> &vec) {
        x = vec.x;
        y = vec.y;
        return *this;
    }
    bool operator==(const Vec2<T> &vec) const {
        return x == vec.x && y == vec.y;
    }
    bool operator!=(const Vec2<T> &vec) const {
        return !(operator==(vec));
    }
    
    template <typename U>
    Vec2<T> operator*(const U u) const {
        return Vec2<T>(x * u, y * u);
    }
    template <typename U>
    Vec2<T>& operator*=(const U u) {
        x *= u;
        y *= u;
        return *this;
    }
    template <typename U>
    Vec2<T> operator/(const U u) const {
        return Vec2<T>(x / u, y / u);
    }
    template <typename U>
    Vec2<T>& operator/=(const U u) {
        x /= u;
        y /= u;
        return *this;
    }
    
    const T& operator[](const int i) const {
        assert(i >= 0 && i < 2);
        if (i == 0) return x;
        return y;
    }
    T& operator[](const int i) {
        assert(i >= 0 && i < 2);
        if (i == 0) return x;
        return y;
    }
    
    friend std::ostream& operator<<(std::ostream &os, const Vec2<T> &vec) {
        return os << vec.x << " " << vec.y << std::endl;
    }
    
    
    T dot(const Vec2<T> &vec) {
        return x * vec.x + y * vec.y;
    }
};

typedef Vec2<double> Vec2d;
typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;

template <typename T>
class Vec3 {
public:
    T x, y, z;
    
    // constructor
    Vec3(): x(0), y(0), z(0) {}
    Vec3(const T &t):x(t), y(t), z(t) {}
    Vec3(const T &x, const T &y, const T &z): x(x), y(y), z(z) {}
    Vec3(const Vec3<T> &vec): x(vec.x), y(vec.y), z(vec.z) {}

    // operator
    Vec3<T> operator+(const Vec3<T> &vec) const {
        return Vec3<T>(x + vec.x, y + vec.y, z + vec.z);
    }
    Vec3<T> operator-(const Vec3<T> &vec) const {
        return Vec3<T>(x - vec.x, y - vec.y, z - vec.z);
    }

    Vec3<T>& operator+=(const Vec3<T> &vec) {
        x += vec.x;
        y += vec.y;
        z += vec.z;
        return *this;
    }
    
    Vec3<T>& operator-=(const Vec3<T> &vec) {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;
        return *this;
    }

    Vec3<T>& operator=(const Vec3<T> &vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        return *this;
    }
    bool operator==(const Vec3<T> &vec) const {
        return x == vec.x && y == vec.y && z == vec.z;
    }
    bool operator!=(const Vec3<T> &vec) const {
        return !(operator==(vec));
    }
    
    template <typename U>
    Vec3<T> operator*(const U u) const {
        return Vec3<T>(x * u, y * u, z * u);
    }
    template <typename U>
    Vec3<T>& operator*=(const U u) {
        x *= u;
        y *= u;
        z *= u;
        return *this;
    }
    template <typename U>
    Vec3<T> operator/(const U u) const {
        return Vec3<T>(x / u, y / u, z / u);
    }
    template <typename U>
    Vec3<T>& operator/=(const U u) {
        x /= u;
        y /= u;
        z /= u;
        return *this;
    }
    
    const T& operator[](const int i) const {
        assert(i >= 0 && i < 3);
        if (i == 0) return x;
        else if (i == 1) return y;
        return z;
    }
    T& operator[](const int i) {
        assert(i >= 0 && i < 3);
        if (i == 0) return x;
        else if (i == 1) return y;
        return z;
    }
    
    friend std::ostream& operator<<(std::ostream &os, const Vec3<T> &vec) {
        return os << vec.x << " " <<  vec.y << " " << vec.z << std::endl;
    }
    
    
    double length2() const {
        return x * x + y * y + z * z;
    }
    double length() const {
        return std::sqrt(length2());
    }
    
    T dot(const Vec3<T> &vec) const {
        return x * vec.x + y * vec.y + z * vec.z;
    }
    
    Vec3<T> cross(const Vec3<T> &vec) const {
        return Vec3<T>(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
    }
    
    Vec3<T> multiply(const Vec3<T> &vec) const {
        return Vec3<T>(x * vec.x, y * vec.y, z * vec.z);
    }
    
    Vec3<T> normalize() const {
        return *this / length();
    }
    
    Vec3<T> interpolate(const Vec3<T> &vec, float factor) const {
        return *this + (vec - *this) * factor;
    }
};

typedef Vec3<double> Vec3d;
typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

template <typename T>
class Vec4 {
public:
    T x, y, z, w;
    
    // constructor
    Vec4(): x(0), y(0), z(0), w(0) {}
    Vec4(const T &t):x(t), y(t), z(t), w(t) {}
    Vec4(const T &x, const T &y, const T &z, const T &w): x(x), y(y), z(z), w(w) {}
    Vec4(const Vec4<T> &vec): x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
    Vec4(const Vec3<T> &vec, const T &w): x(vec.x), y(vec.y), z(vec.z), w(w) {}

    // operator
    Vec4<T> operator+(const Vec4<T> &vec) const {
        return Vec4<T>(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
    }
    Vec4<T> operator-(const Vec4<T> &vec) const {
        return Vec4<T>(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
    }
    Vec4<T>& operator+=(const Vec4<T> &vec) {
        x += vec.x;
        y += vec.y;
        z += vec.z;
        w += vec.w;
        return *this;
    }
    Vec4<T>& operator-=(const Vec4<T> &vec) {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;
        w -= vec.w;
        return *this;
    }
    Vec4<T>& operator=(const Vec4<T> &vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        w = vec.w;
        return *this;
    }
    bool operator==(const Vec4<T> &vec) const {
        return x == vec.x && y == vec.y && z == vec.z && w == vec.w;
    }
    bool operator!=(const Vec4<T> &vec) const {
        return !(operator==(vec));
    }
    
    template <typename U>
    Vec4<T> operator*(const U u) const {
        return Vec4<T>(x * u, y * u, z * u, w * u);
    }
    template <typename U>
    Vec4<T>& operator*=(const U u) {
        x *= u;
        y *= u;
        z *= u;
        w *= u;
        return *this;
    }
    template <typename U>
    Vec4<T> operator/(const U u) const {
        return Vec4<T>(x / u, y / u, z / u, w / u);
    }
    template <typename U>
    Vec4<T>& operator/=(const U u) {
        x /= u;
        y /= u;
        z /= u;
        w /= u;
        return *this;
    }
    
    const T& operator[](const int i) const {
        assert(i >= 0 && i < 4);
        if (i == 0) return x;
        else if (i == 1) return y;
        else if (i == 2) return z;
        return w;
    }
    T& operator[](const int i) {
        assert(i >= 0 && i < 3);
        if (i == 0) return x;
        else if (i == 1) return y;
        else if (i == 2) return z;
        return w;
    }
    
    friend std::ostream& operator<<(std::ostream &os, const Vec4<T> &vec) {
        return os << vec.x << " " <<  vec.y << " " << vec.z << " " << vec.w << std::endl;
    }
    
    
    double length2() const {
        return x * x + y * y + z * z + w * w;
    }
    double length() const {
        return std::sqrt(length2());
    }
    
    T dot(const Vec4<T> &vec) const {
        return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
    }
    
    Vec4<T> multiply(const Vec4<T> &vec) const {
        return Vec4<T>(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
    }
    
    Vec4<T> normalize() const {
        return *this / length();
    }
    
    Vec4<T> interpolate(const Vec4<T> &vec, float factor) const {
        return *this + (vec - *this) * factor;
    }
};

typedef Vec4<double> Vec4d;
typedef Vec4<float> Vec4f;
typedef Vec4<int> Vec4i;

}

#endif /* vector_h */
