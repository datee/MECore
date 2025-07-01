//
// Created by ryen on 3/1/25.
//

#include <spdlog/spdlog.h>

#include "MECore/resource/Material.h"

#include "MECore/render/RenderInterface.h"
#include "MECore/render/pipeline/RenderPipeline.h"

namespace ME::resource {
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
            setItem.arrayElement = 0;

            if (indexes[i] != -1) {
                auto resource = resources[indexes[i]];
                setItem.resourceHandle = resource;

                if (setItem.type == nvrhi::ResourceType::Texture_SRV || setItem.type == nvrhi::ResourceType::Texture_UAV) {
                    auto casted = reinterpret_cast<nvrhi::ITexture*>(resource);
                    const auto& texDesc = casted->getDesc();
                    setItem.dimension = texDesc.dimension;
                    setItem.format = texDesc.format;
                }
            }

            setDesc.addItem(setItem);
        }

        auto temp = device->createBindingSet(setDesc, shader->GetBindingLayout());
        handle = temp;
    }

    bool Material::UpdateBindings() {
        auto nvDevice = render::RenderInterface::instance->GetDevice();
        if (vertexShader) PropertiesToBindings(nvDevice, vertexShader.get(), vertexBindings, vertexResources);
        if (geometryShader) PropertiesToBindings(nvDevice, geometryShader.get(), geometryBindings, geometryResources);
        if (pixelShader) PropertiesToBindings(nvDevice, pixelShader.get(), pixelBindings, pixelResources);
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

    #define PROPRETY_SET(type, prop) if (type##Shader) changed |= SearchAndSet(type##Shader->GetProperties(), type##Resources, property, prop)

    bool Material::SetProperty(const std::string& property, const std::shared_ptr<Texture>& texture) {
        bool changed = false;
        PROPRETY_SET(vertex, texture->GetGPUTexture());
        PROPRETY_SET(geometry, texture->GetGPUTexture());
        PROPRETY_SET(pixel, texture->GetGPUTexture());
        resourcesDirty |= changed;
        return changed;
    }

    bool Material::SetProperty(const std::string& property, const nvrhi::SamplerHandle& sampler) {
        bool changed = false;
        PROPRETY_SET(vertex, sampler);
        PROPRETY_SET(geometry, sampler);
        PROPRETY_SET(pixel, sampler);
        resourcesDirty |= changed;
        return changed;
    }

    #undef PROPRETY_SET

    #define ADD_LAYOUT(cond, source) \
    if (cond) { \
        if (auto layout = source; layout != nullptr) { \
        desc.bindingLayouts.push_back(layout); \
        } \
    } \

    nvrhi::GraphicsPipelineDesc Material::GetGPUPipelineDesc() const {
        auto rasterState = nvrhi::RasterState()
            .setFillSolid()
            .setCullMode(drawSettings.culling)
            .setFrontCounterClockwise(true)
            .setDepthClipEnable(true);
        auto depthStencilState = nvrhi::DepthStencilState()
            .setDepthTestEnable(depthSettings.testEnabled)
            .setDepthWriteEnable(depthSettings.writeEnabled)
            .setDepthFunc(depthSettings.comparison)
            .setStencilEnable(stencilSettings.enabled)
            .setFrontFaceStencil(stencilSettings.front)
            .setBackFaceStencil(stencilSettings.back);
        auto blendState = nvrhi::BlendState()
            .setRenderTarget(0, nvrhi::BlendState::RenderTarget().setColorWriteMask(static_cast<nvrhi::ColorMask>(drawSettings.colorMask)));

        auto renderState = nvrhi::RenderState()
            .setRasterState(rasterState)
            .setDepthStencilState(depthStencilState)
            .setBlendState(blendState);

        auto desc = nvrhi::GraphicsPipelineDesc()
            .setPrimType(nvrhi::PrimitiveType::TriangleList)
            .setRenderState(renderState)
            .setInputLayout(vertexShader->GetInputLayout());

        desc.VS = vertexShader->GetGPUShader();
        if (geometryShader) desc.GS = geometryShader->GetGPUShader();
        desc.PS = pixelShader->GetGPUShader();

        ADD_LAYOUT(true, render::RenderPipeline::instance->GetGlobalBindings())
        ADD_LAYOUT(vertexShader, vertexShader->GetBindingLayout())
        ADD_LAYOUT(geometryShader, geometryShader->GetBindingLayout())
        ADD_LAYOUT(pixelShader, pixelShader->GetBindingLayout())

        return desc;
    }

    #undef ADD_LAYOUT
}
