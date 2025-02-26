//
// Created by ryen on 2/25/25.
//

#include "MECore/render/RenderTexture.h"
#include "MECore/render/RenderInterface.h"

namespace ME::render {
    RenderTexture::RenderTexture(uint32_t width, uint32_t height, nvrhi::Format format) {
        this->width = width;
        this->height = height;
        this->format = format;
        CreateResources();
    }

    RenderTexture::~RenderTexture() {
        texture = nullptr;
        framebuffer = nullptr;
    }

    void RenderTexture::SetSize(uint32_t width, uint32_t height) {
        this->width = width;
        this->height = height;
        CreateResources();
    }

    void RenderTexture::CreateResources() {
        auto device = RenderInterface::instance->GetDevice();

        nvrhi::TextureDesc textureDesc;
        textureDesc.width = width;
        textureDesc.height = height;
        textureDesc.format = format;
        textureDesc.dimension = nvrhi::TextureDimension::Texture2D;
        textureDesc.isRenderTarget = true;
        textureDesc.clearValue = nvrhi::Color(0.0f);
        textureDesc.useClearValue = true;
        textureDesc.initialState = nvrhi::ResourceStates::RenderTarget;
        textureDesc.keepInitialState = true;

        texture = device->createTexture(textureDesc);

        nvrhi::FramebufferDesc framebufferDesc = nvrhi::FramebufferDesc()
            .addColorAttachment(texture);

        framebuffer = device->createFramebuffer(framebufferDesc);
    }
}
