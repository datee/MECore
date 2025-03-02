//
// Created by ryen on 2/20/25.
//

#pragma once

#include <vector>
#include <nvrhi/nvrhi.h>

#include "MECore/math/Types.h"

namespace ME::resource {
    struct MeshStream {
        std::string name;
        nvrhi::Format format;

        virtual ~MeshStream() = default;

        virtual const void* GetData() const = 0;
        virtual size_t GetSize() const = 0;
        virtual size_t GetStride() const = 0;
    };

    template<typename T>
    struct Stream final : public MeshStream {
        std::vector<T> data;

        const void* GetData() const override { return data.data(); }
        size_t GetSize() const override { return data.size() * GetStride(); }
        size_t GetStride() const override { return sizeof(T); }
    };

    class VertexBuffer {
        friend class Mesh;
        bool needsUpdate = false;
        std::vector<MeshStream*> streams;
        nvrhi::BufferHandle buffer;

        public:
        VertexBuffer() = default;

        void Upload(nvrhi::ICommandList* commandList) const;
    };

    // A single mesh.
    class Mesh {
        private:
        bool wantsUpload = false;
        nvrhi::BufferHandle gpuVertexBuffer;
        nvrhi::BufferHandle gpuIndexBuffer;

        public:
        std::vector<PackedVector3> vertices;
        std::vector<uint32_t> indexes;

        Mesh() = default;

        bool WantsUpload() const { return wantsUpload; }
        void WantUpload() { wantsUpload = true; }

        nvrhi::BufferHandle GetVertexBuffer() const { return gpuVertexBuffer; }
        nvrhi::BufferHandle GetIndexBuffer() const { return gpuIndexBuffer; }

        bool CreateGPUBuffers();
        void DestroyGPUBuffers();
        void AddUpload(nvrhi::ICommandList* commandList) const;
    };
}
