//
// Created by ryen on 2/25/25.
//

#pragma once

#include "RenderTarget.h"
#include "Window.h"

namespace ME::render {
    class RenderWindow : public RenderTarget {
        private:
        Window* window;
        std::vector<nvrhi::FramebufferHandle> framebuffers;

        void CreateFramebuffers();
        void DestroyFramebuffers();

        public:
        RenderWindow() = default;
        explicit RenderWindow(Window* window);
        ~RenderWindow() override;

        void GetSize(int* width, int* height) const override {
            window->GetSize(width, height);
        }
        bool CanRender() const override {
            return window && !framebuffers.empty();
        }
        nvrhi::FramebufferHandle GetFramebuffer() const override {
            if (!window) return nullptr;
            return framebuffers[window->GetCurrentSwapchainIndex()];
        }
        Window* GetWindow() const {
            return window;
        }
    };
}
