#pragma once

#include <nvrhi/nvrhi.h>

#include "RenderPipeline.h"

namespace ME::render {
    class ExamplePipeline : public RenderPipeline {
        private:
        nvrhi::CommandListHandle commandList;
        nvrhi::BufferHandle worldBuffer;
        nvrhi::BindingSetHandle bindingSet;

        public:
        ExamplePipeline();

        void AddPass(RenderPass* pass, RenderStage, int order) override;
        void Render(const node::RenderRootNode* root, node::RenderCamera* camera) override;
    };
}
