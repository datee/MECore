//
// Created by ryen on 2/25/25.
//

#pragma once

#include <nvrhi/nvrhi.h>

#include "Viewport.h"

namespace ME::render {
    class RenderTarget : public Viewport {
        public:
        static inline RenderTarget* current;

        virtual bool CanRender() const = 0;
        virtual nvrhi::FramebufferHandle GetFramebuffer() const = 0;

        void MakeCurrent() {
            current = this;
        }
    };
}
