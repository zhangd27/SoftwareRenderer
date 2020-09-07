//
//  color.h
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/19.
//  Copyright © 2020 zhang. All rights reserved.
//

#ifndef color_h
#define color_h

#include <cstdint>
#include "../math/vector.h"


namespace SoftwareRenderer {

class Color: public Vec4f {
public:
    Color();
    Color(float t);
    Color(float r, float g, float b, float a = 255.0f);
    Color(const Vec4f &vec);
    Color(const Vec3f &vec, float a = 255.0f);
    
    uint32_t uint32() const;    
};

}

#endif /* color_h */
