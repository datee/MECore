//
// Created by ryen on 3/1/25.
//

#include "MECore/resource/Material.h"
#include "MECore/render/RenderInterface.h"
#include "MECore/render/pipeline/RenderPipeline.h"

namespace ME::resource {
    bool Material::CreatePipeline(nvrhi::IFramebuffer* framebuffer) {
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

    inline void PropertiesToBindings(nvrhi::IDevice* device, const Shader* shader, nvrhi::BindingSetHandle& handle, std::vector<nvrhi::IResource*>& resources) {
        if (!shader->GetBindingLayout()) return;

        const auto& properties = shader->GetProperties();
        const auto& layoutDesc = shader->GetBindingLayout()->getDesc();

        auto setDesc = nvrhi::BindingSetDesc();

        std::vector<int> indexes;
        indexes.resize(layoutDesc->bindings.size(), -1);
        for (int i = 0; i < properties.size(); i++) {
            const auto& prop = properties[i];
            indexes[prop.index] = i;
        }

        for (int i = 0; i < layoutDesc->bindings.size(); i++) {
            const auto& item = layoutDesc->bindings[i];

            auto setItem = nvrhi::BindingSetItem();
            setItem.type = item.type;
            setItem.slot = item.slot;
            setItem.subresources = nvrhi::AllSubresources;

            if (indexes[i] != -1) {
                setItem.resourceHandle = resources[indexes[i]];
            }

            setDesc.addItem(setItem);
        }

        handle = device->createBindingSet(setDesc, shader->GetBindingLayout());
    }

    bool Material::UpdateBindings() {
        auto nvDevice = render::RenderInterface::instance->GetDevice();

        PropertiesToBindings(nvDevice, vertexShader.get(), vertexBindings, vertexResources);
        PropertiesToBindings(nvDevice, pixelShader.get(), pixelBindings, pixelResources);

        resourcesDirty = false;
        return true;
    }

    inline bool SearchAndSet(const std::vector<ShaderProperty>& properties, std::vector<nvrhi::IResource*>& resources, const std::string& property, nvrhi::IResource* value) {
        for (int i = 0; i < properties.size(); i++) {
            if (properties[i].name == property) {
                resources[i] = value;
                return true;
            }
        }
        return false;
    }

    bool Material::SetProperty(const std::string& property, const std::shared_ptr<Texture>& texture) {
        bool changed = false;
        changed |= SearchAndSet(vertexShader->GetProperties(), vertexResources, property, texture->GetGPUTexture());
        changed |= SearchAndSet(pixelShader->GetProperties(), pixelResources, property, texture->GetGPUTexture());
        resourcesDirty |= changed;
        return changed;
    }

    bool Material::SetProperty(const std::string& property, const nvrhi::SamplerHandle& sampler) {
        bool changed = false;
        changed |= SearchAndSet(vertexShader->GetProperties(), vertexResources, property, sampler);
        changed |= SearchAndSet(pixelShader->GetProperties(), pixelResources, property, sampler);
        resourcesDirty |= changed;
        return changed;
    }
}
