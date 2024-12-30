//
// Created by ryen on 12/9/24.
//

#ifndef SHADER_H
#define SHADER_H
#include <memory>
#include <SDL3/SDL_gpu.h>

#include "AssetBase.h"

namespace me::asset {
    enum class ShaderType {
        Vertex, Fragment
    };

    typedef std::shared_ptr<class Shader> ShaderPtr;

    class Shader : public AssetBase {
        private:
        bool precompiled;
        ShaderType type;
        char* code;
        size_t codeLength;

        SDL_GPUShader* shader;

        public:
        Shader() = delete;
        Shader(bool precompiled, ShaderType type, char* code, size_t codeLength);

        [[nodiscard]] inline bool HasGPUShader() const { return shader != NULL; }
        [[nodiscard]] inline SDL_GPUShader* GetGPUShader() const { return shader; }

        bool CreateGPUShader();
        void DestroyGPUShader();
    };

}

#endif //SHADER_H
