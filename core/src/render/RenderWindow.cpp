//
// Created by ryen on 2/25/25.
//

#include <spdlog/spdlog.h>

#include "MECore/render/RenderWindow.h"
#include "MECore/render/RenderInterface.h"

namespace ME::render {
    RenderWindow::RenderWindow(Window* window) {
        this->window = window;
        this->window->beforeRefresh = [this](){ DestroyFramebuffers(); };
        this->window->afterRefresh = [this](){ CreateFramebuffers(); };
        CreateFramebuffers();
    }

    RenderWindow::~RenderWindow() {
        if (window) {
            window->beforeRefresh = nullptr;
            window->afterRefresh = nullptr;
        }
    }

    void RenderWindow::CreateFramebuffers() {
        int width, height;
        window->GetSize(&width, &height);

        auto nvDevice = RenderInterface::instance->GetDevice();
        auto depthDesc = nvrhi::TextureDesc()
            .setWidth(width)
            .setHeight(height)
            .setFormat(nvrhi::Format::D32S8)
            .setIsRenderTarget(true)
            .setInitialState(nvrhi::ResourceStates::DepthWrite)
            .setKeepInitialState(true);
        depthBuffer = nvDevice->createTexture(depthDesc);

        auto count = window->GetSwapchainCount();
        framebuffers.resize(count);
        for (int i = 0; i < count ; i++) {
            auto frameBufferDesc = nvrhi::FramebufferDesc()
                .addColorAttachment(window->GetSwapchainTexture(i))
                .setDepthAttachment(depthBuffer);
            framebuffers[i] = nvDevice->createFramebuffer(frameBufferDesc);
        }
    }

    void RenderWindow::DestroyFramebuffers() {
        framebuffers.clear();
        depthBuffer = nullptr;
    }
}
