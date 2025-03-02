//
// Created by ryen on 2/25/25.
//

#pragma once

#include "RenderTarget.h"

namespace ME::render {
    class RenderTexture : public RenderTarget {
        private:
        uint32_t width, height;
        nvrhi::Format format;

        nvrhi::TextureHandle texture;
        nvrhi::FramebufferHandle framebuffer;

        void CreateResources();

        public:
        RenderTexture() = default;
        RenderTexture(uint32_t width, uint32_t height, nvrhi::Format format);
        ~RenderTexture() override;

        void GetSize(int* width, int* height) const override {
            *width = this->width;
            *height = this->height;
        }
        bool CanRender() const override {
            return framebuffer != nullptr;
        }
        nvrhi::FramebufferHandle GetFramebuffer() const override {
            return framebuffer;
        }
        nvrhi::ITexture* GetTexture() const {
            return texture;
        }

        void SetSize(uint32_t width, uint32_t height);
    };
}
