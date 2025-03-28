//
// Created by ryen on 2/25/25.
//

#pragma once

#include "RenderPass.h"
#include "MECore/node/render/RenderRootNode.h"

namespace ME::render {
    enum class RenderStage {
        Skybox,
        Opaque,
        Transparent
    };

    class RenderPipeline {
        public:
        static inline RenderPipeline* instance;

        virtual ~RenderPipeline() = default;

        virtual nvrhi::BindingLayoutHandle GetGlobalBindings() = 0;

        // Order: Zero is a valid option but it happens AFTER the stage.
        virtual void AddPass(RenderPass* pass, RenderStage stage, int order) = 0;
        virtual void Render(const node::RenderRootNode* root, node::RenderCamera* camera) = 0;
    };
}
