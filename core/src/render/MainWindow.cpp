//
// Created by ryen on 12/7/24.
//

#include "MainWindow.h"

namespace me::window {
    void OpenWindow(const char* title, const math::IntVector2 size) {
        window = SDL_CreateWindow(title, size.x, size.y, SDL_WINDOW_VULKAN);
        device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, false, NULL);
        SDL_ClaimWindowForGPUDevice(device, window);

        resolution = size;
        aspect = static_cast<float>(size.x) / static_cast<float>(size.y);
    }

    void CloseWindow() {
        SDL_DestroyGPUDevice(device);
        SDL_DestroyWindow(window);
    }
}
