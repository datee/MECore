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
        auto count = window->GetSwapchainCount();
        framebuffers.resize(count);
        for (int i = 0; i < count ; i++) {
            auto desc = nvrhi::FramebufferDesc().addColorAttachment(window->GetSwapchainTexture(i));
            framebuffers[i] = RenderInterface::instance->GetDevice()->createFramebuffer(desc);
        }
    }

    void RenderWindow::DestroyFramebuffers() {
        framebuffers.clear();
    }
}
