//
// Created by ryen on 12/9/24.
//

#include "Shader.h"

#include <SDL3_shadercross/SDL_shadercross.h>

#include "render/RenderGlobals.h"

namespace me::asset {
    inline SDL_GPUShaderStage GetStage(ShaderType type) {
        switch (type) {
            case ShaderType::Vertex:
                return SDL_GPU_SHADERSTAGE_VERTEX;
            case ShaderType::Fragment:
                return SDL_GPU_SHADERSTAGE_FRAGMENT;
        }
        return SDL_GPU_SHADERSTAGE_VERTEX;
    }

    inline const char* GetEntrypoint(ShaderType type) {
        switch (type) {
            case ShaderType::Vertex:
                return "vertex";
            case ShaderType::Fragment:
                return "fragment";
        }
        return nullptr;
    }

    Shader::Shader(bool precompiled, ShaderType type, char* code, size_t codeLength) : AssetBase(u"me.asset.ShaderAsset") {
        this->precompiled = precompiled;
        this->type = type;
        this->code = code;
        this->codeLength = codeLength;
        this->shader = nullptr;
    }

    bool Shader::CreateGPUShader() {
        if (!precompiled) {
            SDL_ShaderCross_GraphicsShaderInfo info;

            shader = SDL_ShaderCross_CompileGraphicsShaderFromHLSL(
                render::mainDevice,
                code,
                GetEntrypoint(type),
                NULL,
                NULL,
                0,
                GetStage(type),
                &info);

            return shader != nullptr;
        } else {

        }
        return false;
    }

    void Shader::DestroyGPUShader() {
        if (!shader) return;
        SDL_ReleaseGPUShader(render::mainDevice, shader);
        shader = nullptr;
    }

}
