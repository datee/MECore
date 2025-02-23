//
// Created by ryen on 12/29/24.
//

#pragma once

#include "RenderInterface.h"

namespace ME::render {
    inline RenderInterface* interface;
    inline std::vector<nvrhi::FramebufferHandle> framebuffers;

    bool Initialize();
    void Shutdown();

    bool BeginFrame();
    nvrhi::FramebufferHandle GetFramebuffer();
    bool Present();
}
