//
//  framebuffer.h
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/23.
//  Copyright © 2020 zhang. All rights reserved.
//

#ifndef framebuffer_h
#define framebuffer_h

#include <vector>
#include "../math/vector.h"
#include "color.h"


namespace SoftwareRenderer {

class Framebuffer {
    std::vector<uint32_t> colorbuffer; // color buffer
    std::vector<float> depthbuffer; // z-buffer
    int width;
    int height;
    
public:
    // constructor
    Framebuffer(int _width, int _height);
    ~Framebuffer() = default;
    
    int getWidth() const {
        return width;
    }
    int getHeight() const {
        return height;
    }
    
    uint32_t* getColorbuffer();
    
    float getDepth(const int &x, const int &y) const;
    
    void clearBuffer();
    
    void setDepth(const int &x, const int &y, const float &depth);
    void setPixelColor(const int &x, const int &y, const Color &color);
    //void setColorAndDepth(const int &x, const int &y, const Color &color, const float &depth);
};
}

#endif /* framebuffer_h */
