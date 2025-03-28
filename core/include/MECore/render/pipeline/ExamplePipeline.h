#pragma once

#include <nvrhi/nvrhi.h>

#include "RenderPipeline.h"

namespace ME::render {
    class ExamplePipeline : public RenderPipeline {
        private:
        nvrhi::CommandListHandle commandList;
        nvrhi::BufferHandle worldBuffer;

        nvrhi::BindingLayoutHandle globalBindingLayout;
        nvrhi::BindingSetHandle globalBindingSet;

        void CreateGlobalBindingLayout();
        void CreateGlobalBindingSet();

        public:
        ExamplePipeline();

        nvrhi::BindingLayoutHandle GetGlobalBindings() override { return globalBindingLayout; }

        void AddPass(RenderPass* pass, RenderStage, int order) override;
        void Render(const node::RenderRootNode* root, node::RenderCamera* camera) override;
    };
}
