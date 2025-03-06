//
// Created by ryen on 2/25/25.
//

#pragma once

#include <nvrhi/nvrhi.h>
#include <MECore/node/render/RenderCamera.h>

namespace ME::render {
    struct RenderPassContext {
        nvrhi::IDevice* device;
        nvrhi::IFramebuffer* target;
        node::RenderCamera* camera;
    };

    class RenderPass {
        public:
        virtual ~RenderPass() = default;

        void Render(const RenderPassContext& context);
    };
}
