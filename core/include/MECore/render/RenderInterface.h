//
// Created by ryen on 2/21/25.
//

#pragma once

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

        virtual void DestroyDevice() = 0;
    };
}
