//
// Created by ryen on 3/27/25.
//

#include "MECore/resource/Texture.h"
#include "MECore/render/RenderInterface.h"

namespace ME::resource {
    bool Texture::ReallocateTexture() {
        auto nvDevice = render::RenderInterface::instance->GetDevice();
        auto desiredDesc = CreateDescriptor();

        if (texture != nullptr) {
            const auto& currDesc = texture->getDesc();

            // TODO: INCOMPLETE COMPARISON, check for more variables
            if (currDesc.width == desiredDesc.width && currDesc.height == desiredDesc.height) return true;
        }

        desiredDesc.dimension = GetDimension();
        desiredDesc.format = GetFormat();
        desiredDesc.initialState = nvrhi::ResourceStates::ShaderResource;
        desiredDesc.keepInitialState = true;

        texture = nvDevice->createTexture(desiredDesc);
        return true;
    }

    bool Texture::UpdateTexture() {
        if (!IsDirty()) return true;

        ReallocateTexture();
        return true;
    }

    void Texture::Upload() {
        auto nvDevice = render::RenderInterface::instance->GetDevice();
        auto cmd = nvDevice->createCommandList();
        cmd->open();
        AddUpload(cmd);
        cmd->close();
        nvDevice->executeCommandList(cmd);
    }

    void Texture::AddUpload(nvrhi::ICommandList* cmd) {
        auto info = nvrhi::getFormatInfo(GetFormat());
        auto pixelByteSize = info.blockSize * info.bytesPerBlock;
        auto rowSize = texture->getDesc().width;

        cmd->writeTexture(texture, 0, 0, GetData(), rowSize * pixelByteSize);
    }
}
