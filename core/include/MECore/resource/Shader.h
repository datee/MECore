//
// Created by ryen on 2/26/25.
//

#pragma once

#include <nvrhi/nvrhi.h>

#include "Resource.h"

namespace ME::resource {
    enum class AttributeType {
        Float
    };

    struct ShaderAttribute {
        std::string name;
    };

    class Shader : public Resource {
        private:
        nvrhi::ShaderType type;
        nvrhi::ShaderHandle shader;
        nvrhi::BindingLayoutHandle bindingLayout;
        nvrhi::InputLayoutHandle inputLayout;

        public:
        Shader() = default;
        Shader(nvrhi::ShaderType type, nvrhi::ShaderHandle shader, nvrhi::BindingLayoutHandle bindingLayout, nvrhi::InputLayoutHandle inputLayout) {
            this->type = type;
            this->shader = shader;
            this->bindingLayout = bindingLayout;
            this->inputLayout = inputLayout;
        }

        nvrhi::ShaderHandle GetGPUShader() const { return shader; }
        nvrhi::BindingLayoutHandle GetBindingLayout() const { return bindingLayout; }
        nvrhi::InputLayoutHandle GetInputLayout() const { return inputLayout; }
    };
}
