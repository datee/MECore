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

    Mesh::Mesh(std::vector<math::Vector3> vertex, std::vector<uint32_t> index) : Mesh() {
        cpuVertexBuffer = std::move(vertex);
        cpuIndexBuffer = std::move(index);
    }


    Mesh::Mesh(math::Vector3* vertex, const uint32_t vertexCount, uint32_t* index, const uint32_t indexCount) : Mesh() {
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
        info.size = sizeof(math::Vector3) * cpuIndexBuffer.size();
        gpuVertexBuffer = SDL_CreateGPUBuffer(window::device, &info);
        if (!gpuVertexBuffer) return false;

        info.usage = SDL_GPU_BUFFERUSAGE_INDEX;
        info.size = sizeof(uint32_t) * cpuIndexBuffer.size();
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
        info.size = (sizeof(math::Vector3) * cpuVertexBuffer.size()) + (sizeof(uint32_t) * cpuIndexBuffer.size());
        info.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;

        SDL_GPUTransferBuffer* transferBuffer = SDL_CreateGPUTransferBuffer(window::device, &info);

        uint32_t vertexPointerSize = sizeof(math::Vector3) * cpuVertexBuffer.size();
        math::Vector3* vertexPointer = static_cast<math::Vector3*>(SDL_MapGPUTransferBuffer(window::device, transferBuffer, false));
        SDL_memcpy(vertexPointer, cpuVertexBuffer.data(), vertexPointerSize);

        uint32_t indexPointerSize = sizeof(uint32_t) * cpuIndexBuffer.size();
        uint32_t* indexPointer = reinterpret_cast<uint32_t*>(vertexPointer + cpuVertexBuffer.size());
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

    bool Mesh::UploadToGPU(SDL_GPUCopyPass* copyPass) const {
        // CREATE TRANSFER BUFFER
        SDL_GPUTransferBufferCreateInfo info;
        info.size = (sizeof(math::Vector3) * cpuVertexBuffer.size()) + (sizeof(uint32_t) * cpuIndexBuffer.size());
        info.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;

        SDL_GPUTransferBuffer* transferBuffer = SDL_CreateGPUTransferBuffer(window::device, &info);
        if (!transferBuffer) return false;

        // VERTEX
        SDL_GPUTransferBufferLocation vertSource;
        vertSource.transfer_buffer = transferBuffer;
        vertSource.offset = 0;

        SDL_GPUBufferRegion vertDestination;
        vertDestination.buffer = gpuVertexBuffer;
        vertDestination.offset = 0;
        vertDestination.size = sizeof(math::Vector3) * cpuVertexBuffer.size();

        SDL_UploadToGPUBuffer(copyPass, &vertSource, &vertDestination, false);

        // INDEX
        SDL_GPUTransferBufferLocation indexSource;
        indexSource.transfer_buffer = transferBuffer;
        indexSource.offset = 0;

        SDL_GPUBufferRegion indexDestination;
        indexDestination.buffer = gpuIndexBuffer;
        indexDestination.offset = 0;
        indexDestination.size = sizeof(uint32_t) * cpuIndexBuffer.size();

        SDL_UploadToGPUBuffer(copyPass, &indexSource, &indexDestination, false);

        // DESTROY TRANSFER BUFFER
        SDL_ReleaseGPUTransferBuffer(window::device, transferBuffer);

        return true;
    }

}
