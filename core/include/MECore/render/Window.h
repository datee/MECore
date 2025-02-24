//
// Created by ryen on 2/24/25.
//

#pragma once

#include <SDL3/SDL.h>
#include <nvrhi/nvrhi.h>

namespace ME::render {
    class Window {
        public:
        virtual bool IsValid() const = 0;

        virtual SDL_Window* GetWindow() const = 0;
        virtual void GetSize(int* width, int* height) const = 0;
        inline float GetAspect() const {
            int width, height;
            GetSize(&width, &height);
            return (float)width / (float)height;
        }

        virtual uint32_t GetSwapchainCount() = 0;
        virtual uint32_t GetCurrentSwapchainIndex() = 0;
        virtual nvrhi::ITexture* GetSwapchainTexture(uint32_t index) = 0;
        virtual nvrhi::ITexture* GetCurrentSwapchainTexture() = 0;

        virtual bool CreateSwapchain() = 0;
        virtual void DestroySwapchain() = 0;
        virtual void Destroy() = 0;

        virtual bool BeginFrame() = 0;
        virtual bool Present() = 0;
    };
}
