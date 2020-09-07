//
//  window.cpp
//  NaiveSoftwareRenderer
//
//  Created by zhang on 2020/08/19.
//  Copyright © 2020 zhang. All rights reserved.
//

#include <ctime>

#include "window.h"
#include "math/transformation.h"
#include "utils/orbitCamera.h"

using SoftwareRenderer::Vec3f;
using SoftwareRenderer::euler_rotate;

Window::Window(int argc_, char** argv_, int width_, int height_, const char *title) {
    width = width_;
    height = height_;
    argc = argc_;
    argv = argv_;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "FAILED TO INITIALIZE" << std::endl;
    }
    
    window = nullptr;
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "FAILED TO CREATE WINDOW" << std::endl;
    }
    
    screen = SDL_GetWindowSurface(window);
    //SDL_FillRect(screen, nullptr, SDL_MapRGBA(screen->format, 0xF0, 0xF0, 0xF0, 0xFF));
    
    quit = false;
    canvas = new SoftwareRenderer::Canvas(static_cast<uint32_t*>(screen->pixels), width, height);
    camera = new SoftwareRenderer::OrbitCamera();
}

Window::~Window() {
    if (canvas) delete canvas;
    if (camera) delete camera;
    canvas = nullptr;
    camera = nullptr;
}

void Window::initialize() {
    canvas->initialize();
    canvas->setViewportMat(0, 0, width, height);
    loadResource();
    setTransMat();
}

void Window::run() {
    auto startTime = std::clock();
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float lastTime = 0.0f;
    
    while (!quit) {
        // Calculate FPS
        float currentFrame = static_cast<float>(clock() - startTime) / CLOCKS_PER_SEC;
        if (currentFrame > lastTime + 2.0f) {
            lastTime = currentFrame;
            std::cout << "FPS: " << 1/deltaTime << std::endl;
        }
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        processInput(deltaTime);
        update();
        clear();
        draw();
        show();
    }
}

void Window::update() {
    canvas->setViewMat(camera->getPosition(), camera->getViewMatrix());
}

void Window::draw() {
    canvas->drawMesh();
}

void Window::show() {
    canvas->drawPixels();
    SDL_UpdateWindowSurface(window);
    
}

void Window::clear() {
    canvas->clearFramebuffer();
}

void Window::processInput(float deltaTime) {
    SDL_Event e;
    static int x, y;
    static bool LeftClick = false;
    static bool RightClick = false;
    
    while (SDL_PollEvent(&e)){
        switch (e.type) {
            case SDL_QUIT:
            {
                quit = true;
                break;
            }
            case SDL_MOUSEWHEEL:
                camera->processMouseScroll(e.wheel.y);
                break;
            case SDL_MOUSEMOTION:
            {
                int xoffset = x - e.motion.x;
                int yoffset = y - e.motion.y;
                x = e.motion.x;
                y = e.motion.y;
                if (LeftClick)
                    camera->processMouseMovement(xoffset, yoffset, SoftwareRenderer::MOUSEBUTTONDOWN::LEFT);
                else if (RightClick)
                    camera->processMouseMovement(xoffset, yoffset, SoftwareRenderer::MOUSEBUTTONDOWN::RIGHT);
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                x = e.button.x;
                y = e.button.y;
                if (e.button.button == SDL_BUTTON_LEFT)
                    LeftClick = true;
                else if (e.button.button == SDL_BUTTON_RIGHT)
                    RightClick = true;
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                LeftClick = false;
                RightClick = false;
                break;
            }
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                    {
                        quit = true;
                        break;
                    }
                    case SDLK_SPACE:
                        canvas->setRenderingMode(); // On/Off WireFrame Mode
                        break;
                    case SDLK_LSHIFT:
                        canvas->setBackFaceCulling(); // On/Off Back Face Culling
                        break;
                    case SDLK_c:
                        camera->reset(); // reset camera and light
                        canvas->resetLight();
                        break;
                    case SDLK_1:
                        canvas->setShader(SoftwareRenderer::ShaderType::Simple);
                        setTransMat();
                        break;
                    case SDLK_2:
                        canvas->setShader(SoftwareRenderer::ShaderType::BlinnPhong);
                        setTransMat();
                        break;
                    // Move Light
                    case SDLK_w:
                        canvas->processKeyInput(deltaTime, SoftwareRenderer::KEYINPUT::W);
                        break;
                    case SDLK_s:
                        canvas->processKeyInput(deltaTime, SoftwareRenderer::KEYINPUT::S);
                        break;
                    case SDLK_a:
                        canvas->processKeyInput(deltaTime, SoftwareRenderer::KEYINPUT::A);
                        break;
                    case SDLK_d:
                        canvas->processKeyInput(deltaTime, SoftwareRenderer::KEYINPUT::D);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

void Window::close() {
    SDL_FreeSurface(screen);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::setTransMat() {
    canvas->setViewMat(camera->getPosition(), camera->getViewMatrix());
    canvas->setProjMat(camera->Zoom, static_cast<float>(width)/height);
    if (argc == 1)
        canvas->setModelMat(SoftwareRenderer::Mat4fIdentity);
    else {
        
    }
}

void Window::loadResource() {
    if (argc == 1) {
        canvas->loadMesh("../resources/flydroid/flydroid.obj", "../resources/flydroid/lambert1_baseColor.png");
    }
    else {
        // load other obj files
    }
}
