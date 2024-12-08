//
// Created by ryen on 12/5/24.
//

#include "Window.h"

me::render::Window::Window() {
    window = SDL_CreateWindow("MANIFOLD ENGINE", 1280, 720, SDL_WINDOW_VULKAN);
    device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, false, NULL);

    SDL_ClaimWindowForGPUDevice(device, window);
}

me::render::Window::~Window() {
    SDL_DestroyGPUDevice(device);
    SDL_DestroyWindow(window);
}

SDL_Window* me::render::Window::GetWindow() const {
    return window;
}

SDL_GPUDevice* me::render::Window::GetDevice() const {
    return device;
}
