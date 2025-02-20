//
// Created by ryen on 12/29/24.
//

#include <nvrhi/vulkan.h>
#include <spdlog/spdlog.h>

#include "RenderGlobals.h"
#include "Window.h"

namespace me::render {
    bool Initialize() {
        nvrhi::vulkan::DeviceDesc deviceDesc;

        mainDevice = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, false, NULL);
        if (!mainDevice) {
            spdlog::critical("Failed to create GPU device. SDL_Error: {}", SDL_GetError());
            return false;
        }
        return true;
    }

    void Shutdown() {
        if (!mainDevice) return;
        if (mainWindow) {
            // DAVR - Deconstruct
            mainWindow = nullptr;
        }
        SDL_DestroyGPUDevice(mainDevice);
    }

    bool CreateMainWindow(const std::string& name, const math::IntVector2& res) {
        if (!mainDevice) return false;
        auto window = Window::Create(name, res);
        if (window) {
            mainWindow = std::unique_ptr<Window>(window);
            return true;
        }
        return false; // If it errored, the create function would've logged it.
    }
}
