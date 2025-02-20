//
// Created by ryen on 12/5/24.
//

#include <spdlog/spdlog.h>

#include "MECore/render/Window.h"
#include "MECore/render/RenderGlobals.h"

namespace ME::render {
    Window::~Window() {
        SDL_DestroyWindow(window);
    }

    Window* Window::Create(const std::string& name, const math::IntVector2& resolution) {
        auto handle = SDL_CreateWindow(name.c_str(), resolution.x, resolution.y, SDL_WINDOW_VULKAN);
        if (!handle) {
            spdlog::critical("Failed to create window {}. SDL_Error: {}", name, SDL_GetError());
            return nullptr;
        }
        if (!SDL_ClaimWindowForGPUDevice(mainDevice, handle)) {
            spdlog::critical("Failed to claim window {} for GPU. SDL_Error: {}", name, SDL_GetError());
            SDL_DestroyWindow(handle);
            return nullptr;
        }

        auto window = new Window();
        window->window = handle;
        window->resolution = resolution;
        window->aspect = static_cast<float>(resolution.x) / static_cast<float>(resolution.y);
        return window;
    }
}

