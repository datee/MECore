//
// Created by ryen on 12/7/24.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_video.h>

#include "../math/Types.h"

namespace me::window {
    inline SDL_Window* window;
    inline SDL_GPUDevice* device;

    inline math::IntVector2 resolution;
    inline float aspect;

    void OpenWindow(const char* title, math::IntVector2 size);
    void CloseWindow();
    void VerifySize();
}

#endif //MAINWINDOW_H
