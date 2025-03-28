//
// Created by ryen on 2/26/25.
//

#pragma once

#include <nvrhi/nvrhi.h>

#include "Resource.h"

namespace ME::resource {
    enum class PropertyType {
        Block, Binding
    };

    struct ShaderProperty {
        std::string name;
        int index;
        nvrhi::ResourceType type;
        uint32_t slot;
    };

    class Shader : public Resource {
        private:
        nvrhi::ShaderType type;
        nvrhi::ShaderHandle shader;
        nvrhi::BindingLayoutHandle bindingLayout;
        nvrhi::InputLayoutHandle inputLayout;

        // TODO: add support for constant buffer properties (floats, vectors)
        std::vector<ShaderProperty> properties;
        std::vector<ShaderProperty> globalProperties;

        public:
        Shader() = default;
        Shader(nvrhi::ShaderType type, nvrhi::ShaderHandle shader, nvrhi::BindingLayoutHandle bindingLayout, nvrhi::InputLayoutHandle inputLayout) {
            this->type = type;
            this->shader = shader;
            this->bindingLayout = bindingLayout;
            this->inputLayout = inputLayout;
        }
        Shader(nvrhi::ShaderType type, nvrhi::ShaderHandle shader, nvrhi::BindingLayoutHandle bindingLayout, nvrhi::InputLayoutHandle inputLayout, std::vector<ShaderProperty> properties, std::vector<ShaderProperty> globalProperties) {
            this->type = type;
            this->shader = shader;
            this->bindingLayout = bindingLayout;
            this->inputLayout = inputLayout;
            this->properties = properties;
            this->globalProperties = globalProperties;
        }

        nvrhi::ShaderHandle GetGPUShader() const { return shader; }
        nvrhi::BindingLayoutHandle GetBindingLayout() const { return bindingLayout; }
        nvrhi::InputLayoutHandle GetInputLayout() const { return inputLayout; }
        const std::vector<ShaderProperty>& GetProperties() const { return properties; }
    };
}
