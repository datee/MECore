//
// Created by ryen on 12/29/24.
//

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

#include "MECore/render/RenderGlobals.h"
#include "MECore/render/VulkanInterface.h"

namespace ME::render {
    bool Initialize() {
        if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
            spdlog::critical("Failed to initialize SDL video subsystem");
            return false;
        }

        interface = new VulkanInterface();
        if (!interface->CreateInstance()) return false;
        if (!interface->CreateDevice()) return false;
        return true;
    }

    void Shutdown() {
        interface->DestroyDevice();
        delete interface;
    }
}
