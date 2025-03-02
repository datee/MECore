//
// Created by ryen on 3/1/25.
//

#include "MECore/resource/Material.h"

namespace ME::resource {
    bool Material::CreateGPUPipeline(nvrhi::IFramebuffer* framebuffer) {
        if (!pipeline) {
            auto nvDevice = render::RenderInterface::instance->GetDevice();
            auto desc = pipelineDesc;
            desc.VS = vertexShader->GetGPUShader();
            desc.PS = pixelShader->GetGPUShader();
            desc.inputLayout = vertexShader->GetInputLayout();
            desc.bindingLayouts = { vertexShader->GetBindingLayout(), pixelShader->GetBindingLayout() };
            pipeline = nvDevice->createGraphicsPipeline(desc, framebuffer);
        }
        return pipeline;
    }

    bool Material::UpdateBindings() {
        auto nvDevice = render::RenderInterface::instance->GetDevice();
        nvrhi::BindingSetDesc bindings;
        bindings.bindings = {
            nvrhi::BindingSetItem::PushConstants(0, 16)
        };
        vertexBindings = nvDevice->createBindingSet(bindings, vertexShader->GetBindingLayout());
        pixelBindings = nvDevice->createBindingSet(bindings, pixelShader->GetBindingLayout());
        return true;
    }
}
