//
// Created by ryen on 2/20/25.
//

#pragma once

#include <vector>
#include <memory>
#include <nvrhi/nvrhi.h>

#include "MECore/math/Types.h"

namespace ME::resource {
    enum class StreamType { Vertex, Index };

    class IMeshStream {
        public:
        virtual ~IMeshStream() = default;

        virtual const std::string& GetName() const = 0;
        virtual const std::string& GetSemantic() const = 0;
        virtual StreamType GetStreamType() const = 0;
        virtual nvrhi::Format GetFormat() const = 0;

        virtual const void* GetData() const = 0;
        virtual size_t GetSize() const = 0;
        virtual size_t GetStride() const = 0;
        size_t GetCount() const { return GetSize() / GetStride(); }

        virtual bool IsDirty() const = 0;
        virtual void ClearDirty() = 0;
    };

    class RawMeshStream : public IMeshStream {
        private:
        std::string name;
        std::string semantic;
        StreamType streamType;
        nvrhi::Format format;

        public:
        void* data;
        size_t size;
        bool isDirty;

        RawMeshStream(const std::string& name, const std::string& semantic, StreamType type, nvrhi::Format format) {
            this->name = name;
            this->semantic = semantic;
            this->streamType = type;
            this->format = format;

            data = nullptr;
            size = 0;
            isDirty = false;
        }
        RawMeshStream(const std::string& semantic, StreamType type, nvrhi::Format format) : RawMeshStream(semantic, semantic, type, format) { }

        const std::string& GetName() const override { return name; }
        const std::string& GetSemantic() const override { return semantic; }
        StreamType GetStreamType() const override { return streamType; }
        nvrhi::Format GetFormat() const override { return format; }

        const void* GetData() const override { return data; }
        size_t GetSize() const override { return size; }
        size_t GetStride() const override { auto info = nvrhi::getFormatInfo(format); return info.blockSize * info.bytesPerBlock; }

        bool IsDirty() const override { return isDirty; }
        void ClearDirty() override { isDirty = false; }
    };

    template<typename T>
    class MeshStreamTemplate : public IMeshStream {
        private:
        std::string name;
        std::string semantic;

        public:
        std::vector<T> data;
        bool isDirty;

        MeshStreamTemplate(const std::string& semantic) {
            this->name = semantic;
            this->semantic = semantic;
            isDirty = false;
        }
        MeshStreamTemplate(const std::string& name, const std::string& semantic) {
            this->name = name;
            this->semantic = semantic;
            isDirty = false;
        }

        const std::string& GetName() const override { return name; }
        const std::string& GetSemantic() const override { return semantic; }

        const void* GetData() const override { return data.data(); }
        size_t GetSize() const override { return data.size() * GetStride(); }
        size_t GetStride() const override { return sizeof(T); }

        bool IsDirty() const override { return isDirty; }
        void ClearDirty() override { isDirty = false; }
    };

    class Vec3MeshStream final : public MeshStreamTemplate<PackedVector3> {
        public:
        Vec3MeshStream(const std::string& semantic) : MeshStreamTemplate(semantic) { }
        Vec3MeshStream(const std::string& name, const std::string& semantic) : MeshStreamTemplate(name, semantic) { }

        StreamType GetStreamType() const override { return StreamType::Vertex; }
        nvrhi::Format GetFormat() const override { return nvrhi::Format::RGB32_FLOAT; }
    };

    class IndexMeshStream final : public MeshStreamTemplate<uint16_t> {
        public:
        IndexMeshStream(const std::string& semantic) : MeshStreamTemplate(semantic) { }
        IndexMeshStream(const std::string& name, const std::string& semantic) : MeshStreamTemplate(name, semantic) { }

        StreamType GetStreamType() const override { return StreamType::Index; }
        nvrhi::Format GetFormat() const override { return nvrhi::Format::R16_UINT; }
    };

    // A single mesh.
    class Mesh {
        private:
        std::unordered_map<IMeshStream*, nvrhi::BufferHandle> gpuBuffers;

        bool ReallocateBuffer(nvrhi::BufferHandle& buffer, IMeshStream* stream);

        public:
        std::vector<std::unique_ptr<IMeshStream>> streams;

        Mesh() = default;

        bool IsDirty() const {
            if (gpuBuffers.size() != streams.size()) return true; // quick check but could be wrong when quick swaps happen
            for (const auto& stream : streams) {
                if (stream->IsDirty()) return true;
            }
            return false;
        }
        IMeshStream* GetStreamBySemantic(const std::string& semantic) const {
            for (const auto& stream : streams) {
                if (stream->GetSemantic() == semantic) return stream.get();
            }
            return nullptr;
        }
        nvrhi::BufferHandle GetBufferBySemantic(const std::string& semantic) const {
            for (const auto& stream : streams) {
                if (stream->GetSemantic() == semantic) return gpuBuffers.at(stream.get());
            }
            return nullptr;
        }

        // COMMON STREAMS AND BUFFERS
        IMeshStream* GetPositionStream() const {
            return GetStreamBySemantic("POSITION");
        }
        nvrhi::BufferHandle GetPositionBuffer() const {
            return GetBufferBySemantic("POSITION");
        }

        IMeshStream* GetIndexStream() const {
            return GetStreamBySemantic("INDEX");
        }
        nvrhi::BufferHandle GetIndexBuffer() const {
            return GetBufferBySemantic("INDEX");
        }

        bool UpdateBuffers();
        void UploadBuffers(nvrhi::ICommandList* cmd);
    };
}
