//
// Created by ryen on 2/25/25.
//

#include "MECore/resource/Mesh.h"
#include "MECore/render/RenderInterface.h"

namespace ME::resource {
    inline void CreateBuffer(nvrhi::IDevice* device, nvrhi::BufferHandle& buffer, uint64_t size, bool indexBuffer) {
        nvrhi::BufferDesc desc;
        desc.byteSize = size;
        desc.structStride = 0;
        desc.canHaveUAVs = false;
        desc.isVertexBuffer = !indexBuffer;
        desc.isIndexBuffer = indexBuffer;
        desc.isDrawIndirectArgs = false;
        desc.isVolatile = false;
        desc.initialState = indexBuffer ? nvrhi::ResourceStates::IndexBuffer : nvrhi::ResourceStates::VertexBuffer;
        desc.keepInitialState = true;

        buffer = device->createBuffer(desc);
    }

    bool Mesh::CreateGPUBuffers() {
        auto nvDevice = render::RenderInterface::instance->GetDevice();

        if (!gpuVertexBuffer) {
            CreateBuffer(nvDevice, gpuVertexBuffer, vertices.size(), false);
        }
        if (!gpuIndexBuffer) {
            CreateBuffer(nvDevice, gpuIndexBuffer, indexes.size() * sizeof(uint32_t), true);
        }

        return true;
    }

    void Mesh::DestroyGPUBuffers() {
        wantsUpload = false;
        gpuVertexBuffer = nullptr;
        gpuIndexBuffer = nullptr;
    }

    // Command list should be open btw.
    void Mesh::AddUpload(nvrhi::ICommandList* commandList) const {
        commandList->writeBuffer(gpuVertexBuffer, vertices.data(), vertices.size());
        commandList->writeBuffer(gpuIndexBuffer, indexes.data(), indexes.size() * sizeof(uint32_t));
    }
}
