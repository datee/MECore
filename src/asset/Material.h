//
// Created by ryen on 12/9/24.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include "AssetBase.h"
#include "Shader.h"

namespace me::asset {
    class Material : public AssetBase {
        private:
        ShaderPtr vertexShader;
        ShaderPtr fragmentShader;

        SDL_GPUGraphicsPipeline* pipeline;

        public:
        Material();
        Material(ShaderPtr vertexShader, ShaderPtr fragmentShader);
        ~Material();

        [[nodiscard]] inline bool HasPipeline() const { return pipeline != nullptr; }
        [[nodiscard]] inline SDL_GPUGraphicsPipeline* GetPipeline() const { return pipeline; }
        [[nodiscard]] inline ShaderPtr GetVertexShader() const { return vertexShader; }
        [[nodiscard]] inline ShaderPtr GetFragmentShader() const { return fragmentShader; }

        bool CreateGPUPipeline();
        void DestroyGPUPipeline();
    };

    typedef std::shared_ptr<Material> MaterialPtr;
}

#endif //MATERIAL_H
