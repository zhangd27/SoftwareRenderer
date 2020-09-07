//
//  camera.h
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/20.
//  Copyright © 2020 zhang. All rights reserved.
//

#ifndef camera_h
#define camera_h

#include "../math/transformation.h"


namespace SoftwareRenderer {

enum class MOUSEBUTTONDOWN {
    LEFT = 0,
    RIGHT = 1
};

class Camera {
public:
    // camera attributes
    static const Vec3f LocalUp;
    static const float Zoom;
    static const float MovementSpeed;
    static const float MouseSense;
    
    // constructor
    Camera() = default;
    virtual ~Camera() {}
    
    virtual Mat4f getViewMatrix() = 0;
    virtual Vec3f getPosition() = 0;
    virtual Vec3f getTarget() = 0;
    virtual void reset() = 0;
    virtual void processMouseScroll(float deltaTime) = 0;
    virtual void processMouseMovement(float xoffset, float yoffset, MOUSEBUTTONDOWN which) = 0;
};
}

#endif /* camera_h */
