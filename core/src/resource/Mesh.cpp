//
// Created by ryen on 2/25/25.
//

#include <spdlog/spdlog.h>

#include "MECore/resource/Mesh.h"
#include "MECore/render/RenderInterface.h"

namespace ME::resource {
    bool Mesh::ReallocateBuffer(nvrhi::BufferHandle& buffer, IMeshStream* stream) {
        if (buffer != nullptr) {
            if (buffer->getDesc().byteSize >= stream->GetSize()) return true;
        }

        bool isIndex = stream->GetStreamType() == StreamType::Index;

        nvrhi::BufferDesc desc;
        desc.byteSize = stream->GetSize();
        desc.structStride = 0;
        desc.canHaveUAVs = false;
        desc.isVertexBuffer = !isIndex;
        desc.isIndexBuffer = isIndex;
        desc.isDrawIndirectArgs = false;
        desc.isVolatile = false;
        desc.initialState = isIndex ? nvrhi::ResourceStates::IndexBuffer : nvrhi::ResourceStates::VertexBuffer;
        desc.keepInitialState = true;
        desc.debugName = stream->GetName().c_str();

        buffer = render::RenderInterface::instance->GetDevice()->createBuffer(desc);
        return buffer != nullptr;
    }

    bool Mesh::UpdateBuffers() {
        if (!IsDirty()) return true;

        for (const auto& stream : streams) {
            if (!gpuBuffers.contains(stream.get()) || stream->IsDirty()) {
                nvrhi::BufferHandle buffer;
                if (!ReallocateBuffer(buffer, stream.get())) return false;
                gpuBuffers[stream.get()] = buffer;
            }
        }

        return true;
    }

    void Mesh::UploadBuffers(nvrhi::ICommandList* cmd) {
        for (const auto& stream : streams) {
            if (!stream->IsDirty()) continue;
            nvrhi::BufferHandle buffer = gpuBuffers[stream.get()];
            cmd->writeBuffer(buffer, stream->GetData(), stream->GetSize());
            stream->ClearDirty();
        }
    }
}
