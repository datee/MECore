//
// Created by ryen on 12/8/24.
//

#include "Mesh.h"

#include <utility>

#include "../render/MainWindow.h"

namespace me::asset {
    Mesh::Mesh() {
        gpuVertexBuffer = nullptr;
        gpuIndexBuffer = nullptr;
    }

    Mesh::Mesh(std::vector<math::PackedVector3> vertex, std::vector<uint16_t> index) : Mesh() {
        cpuVertexBuffer = std::move(vertex);
        cpuIndexBuffer = std::move(index);
    }


    Mesh::Mesh(math::PackedVector3* vertex, const uint32_t vertexCount, uint16_t* index, const uint32_t indexCount) : Mesh() {
        cpuVertexBuffer = std::vector(vertex, vertex + vertexCount);
        cpuIndexBuffer = std::vector(index, index + indexCount);
    }

    Mesh::~Mesh() {
        if (HasGPUBuffers()) {
            DestroyGPUBuffers();
        }
    }

    bool Mesh::CreateGPUBuffers() {
        SDL_GPUBufferCreateInfo info;

        info.usage = SDL_GPU_BUFFERUSAGE_VERTEX;
        info.size = sizeof(math::PackedVector3) * cpuIndexBuffer.size();
        gpuVertexBuffer = SDL_CreateGPUBuffer(window::device, &info);
        if (!gpuVertexBuffer) return false;

        info.usage = SDL_GPU_BUFFERUSAGE_INDEX;
        info.size = sizeof(uint16_t) * cpuIndexBuffer.size();
        gpuIndexBuffer = SDL_CreateGPUBuffer(window::device, &info);
        if (!gpuIndexBuffer) return false;

        return true;
    }

    void Mesh::DestroyGPUBuffers() {
        if (!HasGPUBuffers()) return;

        SDL_ReleaseGPUBuffer(window::device, gpuVertexBuffer);
        SDL_ReleaseGPUBuffer(window::device, gpuIndexBuffer);

        gpuVertexBuffer = nullptr;
        gpuIndexBuffer = nullptr;
    }

    MeshTransfer Mesh::StartTransfer() const {
        SDL_GPUTransferBufferCreateInfo info;
        info.size = (sizeof(math::PackedVector3) * cpuVertexBuffer.size()) + (sizeof(uint16_t) * cpuIndexBuffer.size());
        info.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;

        SDL_GPUTransferBuffer* transferBuffer = SDL_CreateGPUTransferBuffer(window::device, &info);

        uint32_t vertexPointerSize = sizeof(math::PackedVector3) * cpuVertexBuffer.size();
        math::PackedVector3* vertexPointer = static_cast<math::PackedVector3*>(SDL_MapGPUTransferBuffer(window::device, transferBuffer, false));
        SDL_memcpy(vertexPointer, cpuVertexBuffer.data(), vertexPointerSize);

        uint32_t indexPointerSize = sizeof(uint16_t) * cpuIndexBuffer.size();
        uint16_t* indexPointer = reinterpret_cast<uint16_t*>(vertexPointer + cpuVertexBuffer.size());
        SDL_memcpy(indexPointer, cpuIndexBuffer.data(), indexPointerSize);

        SDL_UnmapGPUTransferBuffer(window::device, transferBuffer);

        return (MeshTransfer){
            .buffer = transferBuffer,
            .sections = (std::vector<MeshTransferSection>){
                (MeshTransferSection){
                    .location = {
                        .transfer_buffer = transferBuffer,
                        .offset = 0,
                    },
                    .region = {
                        .buffer = gpuVertexBuffer,
                        .offset = 0,
                        .size = vertexPointerSize,
                    }
                },
                (MeshTransferSection){
                    .location = {
                        .transfer_buffer = transferBuffer,
                        .offset = vertexPointerSize,
                    },
                    .region = {
                        .buffer = gpuIndexBuffer,
                        .offset = 0,
                        .size = indexPointerSize,
                    }
                }
            }
        };
    }
}
