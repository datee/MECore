//
// Created by ryen on 12/29/24.
//

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

#include "MECore/render/RenderGlobals.h"
#include "MECore/render/VulkanInterface.h"

namespace ME::render {
    void CreateFramebuffers() {
        auto count = interface->GetSwapchainCount();
        framebuffers.resize(count);
        for (int i = 0; i < count; i++) {
            auto desc = nvrhi::FramebufferDesc().addColorAttachment(interface->GetSwapchainTexture(i));
            framebuffers[i] = interface->GetDevice()->createFramebuffer(desc);
        }
    }

    bool Initialize() {
        if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
            spdlog::critical("Failed to initialize SDL video subsystem");
            return false;
        }

        interface = new VulkanInterface();
        if (!interface->CreateInstance()) return false;
        if (!interface->CreateDevice()) return false;
        if (!interface->CreateSwapchain()) return false;
        CreateFramebuffers();
        return true;
    }

    void Shutdown() {
        interface->DestroySwapchain();
        interface->DestroyDevice();
        delete interface;
    }

    bool BeginFrame() {
        return interface->BeginFrame();
    }

    nvrhi::FramebufferHandle GetFramebuffer() {
        return framebuffers[interface->GetCurrentSwapchainIndex()];
    }

    bool Present() {
        return interface->Present();
    }
}
