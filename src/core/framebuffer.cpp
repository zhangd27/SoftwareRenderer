//
//  framebuffer.cpp
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/23.
//  Copyright © 2020 zhang. All rights reserved.
//

#include "framebuffer.h"


namespace SoftwareRenderer {

Framebuffer::Framebuffer(int _width, int _height) : width(_width), height(_height) {
    depthbuffer.resize(width * height, 1.0f);
    colorbuffer.resize(width * height, Color(60).uint32());
}

void Framebuffer::clearBuffer() {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            depthbuffer[row*width+col] = 1.0f;
            colorbuffer[row*width+col] = Color(60).uint32();
        }
    }
}

void Framebuffer::setDepth(const int &x, const int &y, const float &depth) {
    if (x < 0 || y < 0 || x >= width || y >= height)
        return;
    
    int index = x + y * width;
    depthbuffer[index] = depth;
}

void Framebuffer::setPixelColor(const int &x, const int &y, const Color &color) {
    if (x < 0 || y < 0 || x >= width || y >= height)
        return;
    
    int index = x + y * width;
    colorbuffer[index] = color.uint32();
}

// for alpha blending
/*
void Framebuffer::setColorAndDepth(const int &x, const int &y, const Color &color, const float &depth) {
    if (x < 0 || y < 0 || x >= width || y >= height)
        return;
    
    int index = x + y * width;
    uint32_t currentColor = colorbuffer[index];
    uint32_t newColor = color.uint32();
    uint32_t a = currentColor & 0xff;
    uint32_t newA = color.uint32() & 0xff;
    
    if (depth < depthbuffer[index]) {
        depthbuffer[index] = depth;
        uint32_t t = 255 - newA;
        colorbuffer[index] = (
            (((((newColor >> 0)  & 0xff) * newA +
               ((currentColor >> 0)  & 0xff) * t) >> 8)) |
            (((((newColor >> 8)  & 0xff) * newA +
               ((currentColor >> 8)  & 0xff) * t)     )  & ~0xff) |
            (((((newColor >> 16) & 0xff) * newA +
               ((currentColor >> 16) & 0xff) * t) << 8)  & ~0xffff) |
            (((((newColor >> 24) & 0xff) * newA +
               ((currentColor >> 24) & 0xff) * t) << 16) & ~0xffffff)
        );
    }
    else {
        uint32_t t = 255 - a;
        colorbuffer[index] = (
            (((((currentColor >> 0)  & 0xff) * a +
               ((newColor >> 0)  & 0xff) * t) >> 8)) |
            (((((currentColor >> 8)  & 0xff) * a +
               ((newColor >> 8)  & 0xff) * t)     )  & ~0xff) |
            (((((currentColor >> 16) & 0xff) * a +
               ((newColor >> 16) & 0xff) * t) << 8)  & ~0xffff) |
            (((((currentColor >> 24) & 0xff) * a +
               ((newColor >> 24) & 0xff) * t) << 16) & ~0xffffff)
        );
    }
}
*/
uint32_t* Framebuffer::getColorbuffer() {
    return colorbuffer.data();
}

float Framebuffer::getDepth(const int &x, const int &y) const {
    if (x < 0 || x >= width || y < 0 || y >= height)
        return 0.0f;
    return depthbuffer[x+y*width];
}

}
