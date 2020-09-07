//
//  window.h
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/19.
//  Copyright © 2020 zhang. All rights reserved.
//

#ifndef window_h
#define window_h

#include <SDL2/SDL.h>
#include "core/canvas.h"
#include "utils/camera.h"


static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;

class Window {
public:
    Window(int argc_, char** argv_, int width_ = SCREEN_WIDTH, int height_ = SCREEN_HEIGHT, const char *title = "Software Renderer");
    ~Window();
    
    void initialize();
    void run();
    void close();

private:
    SDL_Window *window;
    SDL_Surface *screen;
    SoftwareRenderer::Canvas *canvas;
    SoftwareRenderer::Camera *camera;
    
    int width;
    int height;
    bool quit;
    int argc;
    char** argv;
    
    void setTransMat();
    void loadResource();
    
    void update();
    void draw();
    void show();
    void clear();
    void processInput(float deltaTime);
};

#endif /* window_h */
