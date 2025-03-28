//
// Created by ryen on 2/26/25.
//

#pragma once

#include <memory>
#include <nvrhi/nvrhi.h>

#include "MECore/resource/Shader.h"
#include "MECore/resource/Texture.h"

namespace ME::resource {
    class Material {
        private:
        std::shared_ptr<Shader> vertexShader;
        std::shared_ptr<Shader> pixelShader;

        nvrhi::GraphicsPipelineHandle pipeline;
        nvrhi::BindingSetHandle vertexBindings;
        nvrhi::BindingSetHandle pixelBindings;

        // TODO: shaders can only have resource properties for now. change later
        std::vector<nvrhi::IResource*> vertexResources;
        std::vector<nvrhi::IResource*> pixelResources;
        bool resourcesDirty;

        public:
        nvrhi::GraphicsPipelineDesc pipelineDesc;
        nvrhi::BindingSetDesc bindingsDesc;

        Material() = default;

        static constexpr Material Opaque() {
            Material material;

            auto rasterState = nvrhi::RasterState()
                .setFillSolid()
                .setCullBack()
                .setFrontCounterClockwise(true)
                .setDepthClipEnable(true);
            // auto depthStencilState = nvrhi::DepthStencilState()
            //     .disableDepthTest()
            //     .disableDepthWrite()
            //     .disableStencil();
            auto depthStencilState = nvrhi::DepthStencilState()
                .enableDepthTest()
                .enableDepthWrite()
                .setDepthFunc(nvrhi::ComparisonFunc::LessOrEqual);

            material.pipelineDesc.primType = nvrhi::PrimitiveType::TriangleList;
            material.pipelineDesc.renderState.rasterState = rasterState;
            material.pipelineDesc.renderState.depthStencilState = depthStencilState;
            return material;
        }

        static constexpr Material Transparent() {
            Material material;

            nvrhi::BlendState blendState;
            blendState.targets[0]
            .setBlendEnable(true)
            .setSrcBlend(nvrhi::BlendFactor::SrcAlpha)
            .setDestBlend(nvrhi::BlendFactor::InvSrcAlpha)
            .setSrcBlendAlpha(nvrhi::BlendFactor::InvSrcAlpha)
            .setDestBlendAlpha(nvrhi::BlendFactor::Zero);
            auto rasterState = nvrhi::RasterState()
            .setFillSolid()
            .setCullNone()
            .setDepthClipEnable(true);
            auto depthStencilState = nvrhi::DepthStencilState()
            .enableDepthTest()
            .disableDepthWrite()
            .disableStencil()
            .setDepthFunc(nvrhi::ComparisonFunc::GreaterOrEqual);

            nvrhi::RenderState renderState;
            renderState.blendState = blendState;
            renderState.depthStencilState = depthStencilState;
            renderState.rasterState = rasterState;

            material.pipelineDesc.primType = nvrhi::PrimitiveType::TriangleList;
            material.pipelineDesc.renderState = renderState;
            return material;
        }

        nvrhi::GraphicsPipelineHandle GetPipeline() const { return pipeline; }
        nvrhi::BindingSetVector GetBindings() const {
            nvrhi::BindingSetVector bindings;
            if (vertexBindings) bindings.push_back(vertexBindings);
            if (pixelBindings) bindings.push_back(pixelBindings);
            return bindings;
        }

        std::shared_ptr<Shader> GetVertexShader() const { return vertexShader; }
        std::shared_ptr<Shader> GetPixelShader() const { return pixelShader; }

        void SetVertexShader(const std::shared_ptr<Shader>& shader) {
            if (vertexShader != shader) {
                vertexResources.clear();
            }
            vertexShader = shader;
            vertexResources.resize(shader->GetProperties().size());
            resourcesDirty = true;
        }
        void SetPixelShader(const std::shared_ptr<Shader>& shader) {
            if (pixelShader != shader) {
                pixelResources.clear();
            }
            pixelShader = shader;
            pixelResources.resize(shader->GetProperties().size());
            resourcesDirty = true;
        }

        bool SetProperty(const std::string& property, const std::shared_ptr<Texture>& texture);
        bool SetProperty(const std::string& property, const nvrhi::SamplerHandle& sampler);

        bool CreatePipeline(nvrhi::IFramebuffer* framebuffer);
        bool UpdateBindings();
    };
}
