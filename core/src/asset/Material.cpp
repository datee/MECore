//
// Created by ryen on 12/9/24.
//

#include "Material.h"

#include <SDL3/SDL_log.h>

#include "math/Types.h"
#include "render/RenderGlobals.h"
#include "render/Window.h"

namespace me::asset {
    Material::Material() : AssetBase(u"me.asset.MaterialAsset") {
        pipeline = nullptr;
    }

    Material::Material(ShaderPtr vertexShader, ShaderPtr fragmentShader) : Material() {
        this->vertexShader = vertexShader;
        this->fragmentShader = fragmentShader;
    }

    Material::~Material() {
        if (HasPipeline()) {
            DestroyGPUPipeline();
        }
    }

    bool Material::CreateGPUPipeline() {
        if (HasPipeline()) {
            DestroyGPUPipeline();
        }

        if (!vertexShader->HasGPUShader()) {
            if (!vertexShader->CreateGPUShader()) {
                SDL_Log("Failed to create GPU vertex shader!");
            }
        }
        if (!fragmentShader->HasGPUShader()) {
            if (!fragmentShader->CreateGPUShader()) {
                SDL_Log("Failed to create GPU fragment shader!");
            }
        }

        // Should this class maintain graphics pipelines? it is meant to be an asset...
        const SDL_GPUGraphicsPipelineCreateInfo info = {
            .vertex_shader = vertexShader->GetGPUShader(),
            .fragment_shader = fragmentShader->GetGPUShader(),
            .vertex_input_state = {
                .vertex_buffer_descriptions = (SDL_GPUVertexBufferDescription[]){
                    {
                        .slot = 0,
                        .pitch = sizeof(math::PackedVector3),
                        .input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
                        .instance_step_rate = 0,
                    }
                },
                .num_vertex_buffers = 1,
                .vertex_attributes = (SDL_GPUVertexAttribute[]){
                    {
                        .location = 0,
                        .buffer_slot = 0,
                        .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
                        .offset = 0,
                    }
                },
                .num_vertex_attributes = 1,
            },
            .primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
            .rasterizer_state = {
                .fill_mode = SDL_GPU_FILLMODE_FILL,
            },
            .target_info = {
                .color_target_descriptions = (SDL_GPUColorTargetDescription[]){
                    { .format = SDL_GetGPUSwapchainTextureFormat(render::mainDevice, render::mainWindow->GetWindow()) }
                },
                .num_color_targets = 1,
            },
        };

        pipeline = SDL_CreateGPUGraphicsPipeline(render::mainDevice, &info);
        if (pipeline == nullptr) {
            SDL_Log("Failed to create graphics pipeline");
            return false;
        }
        return true;
    }

    void Material::DestroyGPUPipeline() {
        SDL_ReleaseGPUGraphicsPipeline(render::mainDevice, pipeline);
        pipeline = nullptr;
    }
}
