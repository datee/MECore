//
// Created by ryen on 2/21/25.
//

#pragma once

#include <SDL3/SDL.h>
#include <nvrhi/nvrhi.h>

#include "Window.h"

namespace ME::render {
    struct DefaultMessageCallback : public nvrhi::IMessageCallback {
        static DefaultMessageCallback& GetInstance();

        void message(nvrhi::MessageSeverity severity, const char* messageText) override;
    };

    class RenderInterface {
        public:
        static inline RenderInterface* instance;

        virtual ~RenderInterface() = default;

        virtual nvrhi::IDevice* GetDevice() = 0;

        virtual bool CreateInstance() = 0;
        virtual bool CreateDevice() = 0;
        virtual void DestroyDevice() = 0;

        virtual Window* CreateWindow(WindowParameters* params) = 0;
    };
}
