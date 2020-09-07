//
//  transformation.h
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/20.
//  Copyright © 2020 zhang. All rights reserved.
//

#ifndef transformation_h
#define transformation_h

#include <cmath>
#include "matrix.h"
#include "constants.h"

namespace SoftwareRenderer {

inline float radian(float angle) {
    return angle * PI / 180;
}

Mat4f inverse(const Mat4f&);

Mat4f translate(const Vec3f&);
Mat4f scale(const float, const float, const float);
Mat4f euler_rotate(const float, const Vec3f&);

// projection matrix
Mat4f ortho(const float, const float, const float, const float, const float, const float);
Mat4f perspective(const float, const float, const float, const float);

// lookat
Mat4f lookat(const Vec3f&, const Vec3f&, const Vec3f&);

// glViewport
Mat4f viewport_trans(const int, const int, const int, const int);
}

#endif /* transformer_h */
