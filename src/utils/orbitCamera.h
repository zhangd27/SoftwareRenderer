//
//  orbitCamera.h
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/22.
//  Copyright © 2020 zhang. All rights reserved.
//

#ifndef orbitCamera_h
#define orbitCamera_h

#include "camera.h"


namespace SoftwareRenderer {

class OrbitCamera : public Camera {
public:
    OrbitCamera();
    virtual ~OrbitCamera() = default;
    
    virtual Mat4f getViewMatrix() override;
    virtual Vec3f getPosition() override;
    virtual Vec3f getTarget() override;
    virtual void reset() override;
    virtual void processMouseScroll(float yoffset) override;
    virtual void processMouseMovement(float xoffset, float yoffset, MOUSEBUTTONDOWN which) override;
    
private:
    Vec3f Position;
    Vec3f Target;
    
    float theta, phi;
    float radius;
    void update();
    void init();
};
}

#endif /* orbitCamera_h */
