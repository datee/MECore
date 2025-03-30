//
// Created by ryen on 2/25/25.
//

#include "MECore/render/RenderTexture.h"
#include "MECore/render/RenderInterface.h"

namespace ME::render {
    RenderTexture::RenderTexture(uint32_t width, uint32_t height, nvrhi::Format colorFormat, nvrhi::Format depthFormat) {
        this->width = width;
        this->height = height;
        this->colorFormat = colorFormat;
        this->depthFormat = depthFormat;
        CreateResources();
    }

    RenderTexture::~RenderTexture() {
        colorTexture = nullptr;
        depthTexture = nullptr;
        framebuffer = nullptr;
    }

    void RenderTexture::SetSize(uint32_t width, uint32_t height) {
        this->width = width;
        this->height = height;
        CreateResources();
    }

    void RenderTexture::CreateResources() {
        auto device = RenderInterface::instance->GetDevice();

        auto framebufferDesc = nvrhi::FramebufferDesc();
        if (colorFormat != nvrhi::Format::UNKNOWN) {
            nvrhi::TextureDesc textureDesc;
            textureDesc.width = width;
            textureDesc.height = height;
            textureDesc.format = colorFormat;
            textureDesc.dimension = nvrhi::TextureDimension::Texture2D;
            textureDesc.isRenderTarget = true;
            textureDesc.clearValue = nvrhi::Color(0.0f);
            textureDesc.useClearValue = true;
            textureDesc.initialState = nvrhi::ResourceStates::RenderTarget;
            textureDesc.keepInitialState = true;

            colorTexture = device->createTexture(textureDesc);
            framebufferDesc.addColorAttachment(colorTexture);
        }

        if (depthFormat != nvrhi::Format::UNKNOWN) {
            nvrhi::TextureDesc textureDesc;
            textureDesc.width = width;
            textureDesc.height = height;
            textureDesc.format = depthFormat;
            textureDesc.dimension = nvrhi::TextureDimension::Texture2D;
            textureDesc.isRenderTarget = true;
            textureDesc.clearValue = nvrhi::Color(1.0f);
            textureDesc.useClearValue = true;
            textureDesc.initialState = nvrhi::ResourceStates::DepthWrite;
            textureDesc.keepInitialState = true;

            depthTexture = device->createTexture(textureDesc);
            framebufferDesc.setDepthAttachment(depthTexture);
        }

        framebuffer = device->createFramebuffer(framebufferDesc);
    }
}
