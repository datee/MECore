//
// Created by ryen on 12/11/24.
//

#include "SimpleRenderPipeline.h"

#include "MainWindow.h"
#include "../scene/sceneobj/SceneMesh.h"

namespace me::render {
    struct MatrixBuffer {
        math::Matrix4x4 model;
        math::Matrix4x4 view;
        math::Matrix4x4 proj;
    };

    SimpleRenderPipeline::SimpleRenderPipeline(asset::MaterialPtr material) {
        this->material = material;
        material->CreateGPUPipeline();
        pipeline = material->GetPipeline();
    }

    void SimpleRenderPipeline::Render(scene::SceneWorld* world) {
        auto list = world->GetSceneObjects();
        std::vector<scene::SceneMesh*> meshes;
        std::vector<asset::MeshTransfer> transfers;

        for (scene::SceneObject* obj : list) {
            scene::SceneMesh* meshObj = dynamic_cast<scene::SceneMesh*>(obj);
            if (meshObj == nullptr) continue;

            meshes.push_back(meshObj);
            if (!meshObj->mesh->HasGPUBuffers()) {
                meshObj->mesh->CreateGPUBuffers();
                transfers.push_back(meshObj->mesh->StartTransfer());
            }
        }

        if (!transfers.empty()) {
            SDL_GPUCommandBuffer* transferCmd = SDL_AcquireGPUCommandBuffer(window::device);
            SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(transferCmd);

            for (asset::MeshTransfer& transfer : transfers) {
                for (asset::MeshTransferSection& section : transfer.sections) {
                    SDL_UploadToGPUBuffer(copyPass, &section.location, &section.region, false);
                }
            }
            SDL_EndGPUCopyPass(copyPass);

            for (asset::MeshTransfer& transfer : transfers) {
                // releasing before submitting looks wrong but it does it during a submit
                SDL_ReleaseGPUTransferBuffer(window::device, transfer.buffer);
            }

            SDL_SubmitGPUCommandBuffer(transferCmd);
        }

        SDL_GPUCommandBuffer* cmdBuf = SDL_AcquireGPUCommandBuffer(window::device);
        SDL_GPUTexture* swapchainTex;
        if (!SDL_AcquireGPUSwapchainTexture(cmdBuf, window::window, &swapchainTex, NULL, NULL)) {
            return;
        }
        if (swapchainTex == nullptr) return;

        const SDL_GPUColorTargetInfo colorTargetInfo = {
            .texture = swapchainTex,
            .clear_color = (SDL_FColor){ 0.2f, 0.2f, 0.2f, 1.0f },
            .load_op = SDL_GPU_LOADOP_CLEAR,
            .store_op = SDL_GPU_STOREOP_STORE
        };

        SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(cmdBuf, &colorTargetInfo, 1, NULL);
        SDL_BindGPUGraphicsPipeline(renderPass, material->GetPipeline());

        math::Matrix4x4 view = world->GetCamera().GetTransform().ToMatrix();
        math::Matrix4x4 proj = world->GetCamera().GetProjectionMatrix();
        for (scene::SceneMesh* mesh : meshes) {
            math::Matrix4x4 model = mesh->GetTransform().ToMatrix();
            MatrixBuffer matrices = { model, view, proj };

            SDL_GPUBufferBinding vertexBinding = { mesh->mesh->GetGPUVertexBuffer(), 0 };
            SDL_GPUBufferBinding indexBinding = { mesh->mesh->GetGPUIndexBuffer(), 0 };
            SDL_BindGPUVertexBuffers(renderPass, 0, &vertexBinding, 1);
            SDL_BindGPUIndexBuffer(renderPass, &indexBinding, SDL_GPU_INDEXELEMENTSIZE_32BIT);
            SDL_PushGPUVertexUniformData(cmdBuf, 0, &matrices, sizeof(matrices));
            SDL_DrawGPUIndexedPrimitives(renderPass, mesh->mesh->GetIndexBuffer().size(), 1, 0, 0, 0);
        }
        SDL_EndGPURenderPass(renderPass);
        SDL_SubmitGPUCommandBuffer(cmdBuf);
    }
}
