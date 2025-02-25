//
// Created by ryen on 2/24/25.
//

#pragma once

#include <functional>
#include <SDL3/SDL.h>
#include <nvrhi/nvrhi.h>

namespace ME::render {
    class Window {
        public:
        std::function<void()> beforeRefresh;
        std::function<void()> afterRefresh;

        virtual bool IsValid() const = 0;

        virtual SDL_Window* GetWindow() const = 0;
        virtual std::string GetTitle() const = 0;
        virtual void GetSize(int* width, int* height) const = 0;
        inline float GetAspect() const {
            int width, height;
            GetSize(&width, &height);
            return (float)width / (float)height;
        }
        virtual bool GetFullscreen() const = 0;

        virtual uint32_t GetSwapchainCount() = 0;
        virtual uint32_t GetCurrentSwapchainIndex() = 0;
        virtual nvrhi::ITexture* GetSwapchainTexture(uint32_t index) = 0;
        virtual nvrhi::ITexture* GetCurrentSwapchainTexture() = 0;

        virtual void SetTitle(const std::string& name) = 0;
        virtual void SetSize(int width, int height) = 0;
        virtual void SetFullscreen(bool fullscreen) = 0;

        virtual bool CreateSwapchain() = 0;
        virtual void DestroySwapchain() = 0;
        virtual void RefreshSwapchain() = 0;
        virtual void Destroy() = 0;

        virtual bool BeginFrame() = 0;
        virtual bool Present() = 0;
    };
}
