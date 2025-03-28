//
// Created by ryen on 3/1/25.
//

#include "MECore/resource/Material.h"
#include "MECore/render/pipeline/RenderPipeline.h"

namespace ME::resource {
    bool Material::CreateGPUPipeline(nvrhi::IFramebuffer* framebuffer) {
        if (!pipeline) {
            auto nvDevice = render::RenderInterface::instance->GetDevice();
            auto desc = pipelineDesc;
            desc.inputLayout = vertexShader->GetInputLayout();
            desc.VS = vertexShader->GetGPUShader();
            desc.PS = pixelShader->GetGPUShader();
            if (auto layout = render::RenderPipeline::instance->GetGlobalBindings(); layout != nullptr) {
                desc.bindingLayouts.push_back(layout);
            }
            if (auto layout = vertexShader->GetBindingLayout(); layout != nullptr) {
                desc.bindingLayouts.push_back(layout);
            }
            if (auto layout = pixelShader->GetBindingLayout(); layout != nullptr) {
                desc.bindingLayouts.push_back(layout);
            }
            pipeline = nvDevice->createGraphicsPipeline(desc, framebuffer);
        }
        return pipeline;
    }

    bool Material::UpdateBindings() {
        auto nvDevice = render::RenderInterface::instance->GetDevice();

        // VERTEX
        // {
        //     // nvrhi::BindingSetDesc bindings;
        //     // for (const auto& item : vertexShader->GetBindingLayout()->getDesc()->bindings) {
        //     //     bindings.bindings.
        //     // }
        //     vertexBindings = nvDevice->createBindingSet(bindings, vertexShader->GetBindingLayout());
        // }
//
        // pixelBindings = nvDevice->createBindingSet(bindings, pixelShader->GetBindingLayout());
        return true;
    }
}
