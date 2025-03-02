//
// Created by ryen on 2/26/25.
//

#pragma once

#include <nvrhi/nvrhi.h>

#include "MECore/render/RenderInterface.h"
#include "MECore/resource/Shader.h"

namespace ME::resource {
    class Material {
        private:
        nvrhi::GraphicsPipelineHandle pipeline;
        nvrhi::BindingSetHandle vertexBindings;
        nvrhi::BindingSetHandle pixelBindings;

        public:
        Shader* vertexShader;
        Shader* pixelShader;
        nvrhi::GraphicsPipelineDesc pipelineDesc;
        nvrhi::BindingSetDesc bindingsDesc;

        Material() = default;

        static constexpr Material Opaque() {
            Material material;

            auto rasterState = nvrhi::RasterState()
                .setFillSolid()
                .setCullBack()
                .setDepthClipEnable(true);
            auto depthStencilState = nvrhi::DepthStencilState()
                .enableDepthTest()
                .enableDepthWrite()
                .setDepthFunc(nvrhi::ComparisonFunc::GreaterOrEqual);

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
        nvrhi::BindingSetVector GetBindings() const { return { vertexBindings, pixelBindings }; }

        bool CreateGPUPipeline(nvrhi::IFramebuffer* framebuffer);
        bool UpdateBindings();
    };
}
