//
//  texture.h
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/21.
//  Copyright © 2020 zhang. All rights reserved.
//

#ifndef texture_h
#define texture_h

#include "color.h"


namespace SoftwareRenderer {

class Texture2D {
public:
    Texture2D() : width(0), height(0), channel(0), buffer(nullptr) {}
    ~Texture2D();
    
    bool readImage(const char *path);
    
    Color sampler(const float &u, const float &v) const;
    
private:
    int width;
    int height;
    int channel;
    
    unsigned char *buffer;
};

}

#endif /* texture_h */
