//
// Created by ryen on 12/7/24.
//

#ifndef RENDERPASS_H
#define RENDERPASS_H

#include <memory>
#include "SDL3/SDL_gpu.h"
#include "../scene/sceneobj/SceneWorld.h"

namespace me::render {
    class RenderPass {
        virtual void ConfigurePass(SDL_GPUColorTargetInfo& color, SDL_GPUDepthStencilTargetInfo& depth);
        virtual void Render();
    };

    typedef std::shared_ptr<RenderPass> RenderPassPtr;
}

#endif //RENDERPASS_H
