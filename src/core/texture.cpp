//
//  texture.cpp
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/21.
//  Copyright © 2020 zhang. All rights reserved.
//

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "texture.h"


namespace SoftwareRenderer {

Texture2D::~Texture2D() {
    stbi_image_free(buffer);
    buffer = nullptr;
}

bool Texture2D::readImage(const char *path) {
    stbi_set_flip_vertically_on_load(true);
    if (buffer) {
        delete buffer;
    }
    buffer = nullptr;
    buffer = stbi_load(path, &width, &height, &channel, 0);
    if (buffer == nullptr) {
        std::cout << "FAILED TO LOAD TEXTURE" << std::endl;
        return 0;
    }
    
    return 1;
}

Color Texture2D::sampler(const float &u, const float &v) const {
    if (buffer == nullptr) return Color();
    
    unsigned int x = 0, y = 0;
    // bilinear interpolation.
    float factorU = 0, factorV = 0;

    // calculate the corresponding coordinate.
    if (u >= 0.0f && u <= 1.0f && v >= 0.0f && v <= 1.0f) {
        float trueU = u * (width - 1);
        float trueV = v * (height - 1);
        x = static_cast<unsigned int>(trueU);
        y = static_cast<unsigned int>(trueV);
        factorU = trueU - x;
        factorV = trueV - y;
    }
    else {
        float u_ = u, v_ = v;
        if (u > 1.0f)
            u_ = u - static_cast<int>(u);
        else
            u_ = 1.0f - (static_cast<int>(u) - u);
        if (v > 1.0f)
            v_ = v - static_cast<int>(v);
        else
            v_ = 1.0f - (static_cast<int>(v) - v);
        
        float trueU = u_ * (width - 1);
        float trueV = v_ * (height - 1);
        x = static_cast<unsigned int>(trueU);
        y = static_cast<unsigned int>(trueV);
        factorU = trueU - x;
        factorV = trueV - y;
    }

    // texel fetching.
    Vec4f texels[4];
    int index[4];
    index[0] = (x + y * width) * channel;
    if(x + 1 >= width)
        index[1] = index[0];
    else
        index[1] = (x + 1 + y * width) * channel;
    if(y + 1 >= height || x + 1 >= width)
        index[2] = index[0];
    else
        index[2] = (x + 1 + (y + 1) * width) * channel;
    if(y + 1 >= height)
        index[3] = index[0];
    else
        index[3] = (x + (y + 1) * width) * channel;
    
    /* ***********************************
                    |
         texels[3]  |   texels[2]
                    |
     --------------------------------
                    |
         texels[0]  |   texels[1]
                    |
     
     Color = (c_0 * (1 - fu) + c_1 * fu) * (1 - fv) + (c_3 * (1 - fu) + c_2 * fu) * fv
    *************************************** */
    
    if (channel == 1) {          // LUMINANCE
        texels[0].x = texels[0].y = texels[0].z = static_cast<float>(buffer[index[0]]);
        texels[1].x = texels[1].y = texels[1].z = static_cast<float>(buffer[index[1]]);
        texels[2].x = texels[2].y = texels[2].z = static_cast<float>(buffer[index[2]]);
        texels[3].x = texels[3].y = texels[3].z = static_cast<float>(buffer[index[3]]);
            
        texels[0].w = texels[1].w = texels[2].w = texels[3].w = 255.0f;
    }
    else if (channel == 2) {     // LUMINANCE_ALPHA
        texels[0].x = texels[0].y = texels[0].z = static_cast<float>(buffer[index[0]]);
        texels[1].x = texels[1].y = texels[1].z = static_cast<float>(buffer[index[1]]);
        texels[2].x = texels[2].y = texels[2].z = static_cast<float>(buffer[index[2]]);
        texels[3].x = texels[3].y = texels[3].z = static_cast<float>(buffer[index[3]]);
            
        texels[0].w = static_cast<float>(buffer[index[0] + 1]);
        texels[1].w = static_cast<float>(buffer[index[1] + 1]);
        texels[2].w = static_cast<float>(buffer[index[2] + 1]);
        texels[3].w = static_cast<float>(buffer[index[3] + 1]);
    }
    else if (channel == 3) {     // RGB
        texels[0].x = static_cast<float>(buffer[index[0] + 0]);
        texels[0].y = static_cast<float>(buffer[index[0] + 1]);
        texels[0].z = static_cast<float>(buffer[index[0] + 2]);

        texels[1].x = static_cast<float>(buffer[index[1] + 0]);
        texels[1].y = static_cast<float>(buffer[index[1] + 1]);
        texels[1].z = static_cast<float>(buffer[index[1] + 2]);

        texels[2].x = static_cast<float>(buffer[index[2] + 0]);
        texels[2].y = static_cast<float>(buffer[index[2] + 1]);
        texels[2].z = static_cast<float>(buffer[index[2] + 2]);

        texels[3].x = static_cast<float>(buffer[index[3] + 0]);
        texels[3].y = static_cast<float>(buffer[index[3] + 1]);
        texels[3].z = static_cast<float>(buffer[index[3] + 2]);
            
        texels[0].w = texels[1].w = texels[2].w = texels[3].w = 255.0f;
    }
    else {                      // RGBA
        texels[0].x = static_cast<float>(buffer[index[0] + 0]);
        texels[0].y = static_cast<float>(buffer[index[0] + 1]);
        texels[0].z = static_cast<float>(buffer[index[0] + 2]);
        texels[0].w = static_cast<float>(buffer[index[0] + 3]);

        texels[1].x = static_cast<float>(buffer[index[1] + 0]);
        texels[1].y = static_cast<float>(buffer[index[1] + 1]);
        texels[1].z = static_cast<float>(buffer[index[1] + 2]);
        texels[1].w = static_cast<float>(buffer[index[1] + 3]);

        texels[2].x = static_cast<float>(buffer[index[2] + 0]);
        texels[2].y = static_cast<float>(buffer[index[2] + 1]);
        texels[2].z = static_cast<float>(buffer[index[2] + 2]);
        texels[2].w = static_cast<float>(buffer[index[2] + 3]);

        texels[3].x = static_cast<float>(buffer[index[3] + 0]);
        texels[3].y = static_cast<float>(buffer[index[3] + 1]);
        texels[3].z = static_cast<float>(buffer[index[3] + 2]);
        texels[3].w = static_cast<float>(buffer[index[3] + 3]);
    }
    
    // bilinear interpolation.
    texels[0] = texels[0] * (1.0 - factorU) + texels[1] * factorU;
    texels[3] = texels[3] * (1.0 - factorU) + texels[2] * factorU;
    
    return Color(texels[0] * (1.0 - factorV) + texels[3] *factorV);
}

}
