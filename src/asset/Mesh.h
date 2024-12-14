//
// Created by ryen on 12/7/24.
//

#ifndef MESH_H
#define MESH_H

#include <vector>
#include <SDL3/SDL_gpu.h>

#include "../math/Types.h"
#include "AssetBase.h"

namespace me::asset {
    struct MeshTransferSection {
        SDL_GPUTransferBufferLocation location;
        SDL_GPUBufferRegion region;
    };

    struct MeshTransfer {
        SDL_GPUTransferBuffer* buffer;
        std::vector<MeshTransferSection> sections;
    };

    // Stores a single mesh.
    class Mesh : public AssetBase {
        private:
        std::vector<math::Vector3> cpuVertexBuffer;
        std::vector<uint16_t> cpuIndexBuffer;

        SDL_GPUBuffer* gpuVertexBuffer;
        SDL_GPUBuffer* gpuIndexBuffer;

        public:
        Mesh();
        Mesh(std::vector<math::Vector3> vertex, std::vector<uint16_t> index);
        Mesh(math::Vector3* vertex, const uint32_t vertexCount, uint16_t* index, const uint32_t indexCount);
        ~Mesh();

        [[nodiscard]] inline std::vector<math::Vector3>& GetVertexBuffer() { return cpuVertexBuffer; }
        [[nodiscard]] inline std::vector<uint16_t>& GetIndexBuffer() { return cpuIndexBuffer; }

        [[nodiscard]] inline bool HasGPUBuffers() const { return gpuVertexBuffer && gpuIndexBuffer; }
        [[nodiscard]] inline SDL_GPUBuffer* GetGPUVertexBuffer() const { return gpuVertexBuffer; }
        [[nodiscard]] inline SDL_GPUBuffer* GetGPUIndexBuffer() const { return gpuIndexBuffer; }

        bool CreateGPUBuffers();
        void DestroyGPUBuffers();

        [[nodiscard]] MeshTransfer StartTransfer() const;
    };

    typedef std::shared_ptr<Mesh> MeshPtr;
}

#endif //MESH_H
