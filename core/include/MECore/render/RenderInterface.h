//
// Created by ryen on 2/21/25.
//

#pragma once

#include <SDL3/SDL.h>
#include <nvrhi/nvrhi.h>

namespace ME::render {
    struct DefaultMessageCallback : public nvrhi::IMessageCallback {
        static DefaultMessageCallback& GetInstance();

        void message(nvrhi::MessageSeverity severity, const char* messageText) override;
    };

    class RenderInterface {
        public:
        virtual ~RenderInterface() = default;

        virtual bool CreateInstance() = 0;
        virtual bool CreateDevice() = 0;
        virtual bool CreateSwapchain() = 0;

        virtual void DestroyDevice() = 0;
        virtual void DestroySwapchain() = 0;

        virtual void ResizeSwapchain() = 0;

        virtual nvrhi::IDevice* GetDevice() = 0;
        virtual bool BeginFrame() = 0;
        virtual bool Present() = 0;

        virtual Uint32 GetSwapchainCount() = 0;
        virtual Uint32 GetCurrentSwapchainIndex() = 0;
        virtual nvrhi::ITexture* GetSwapchainTexture(Uint32 index) = 0;
        virtual nvrhi::ITexture* GetCurrentSwapchainTexture() = 0;

        // Plan to eventually remove this. Windows will be a different class for multiple viewports.
        virtual SDL_Window* GetWindow() = 0;
        virtual float GetWindowAspect() = 0;
    };
}
