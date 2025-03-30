//
// Created by ryen on 2/26/25.
//

#pragma once

#include <memory>
#include <nvrhi/nvrhi.h>

#include "MECore/resource/Resource.h"
#include "MECore/resource/Shader.h"
#include "MECore/resource/Texture.h"

namespace ME::resource {
    enum class ColorMask : uint8_t {
        None = 0,
        Red = 1,
        Green = 2,
        Blue = 4,
        Alpha = 8,
        All = 0xF
    };

    struct MaterialDrawSettings {
        nvrhi::RasterCullMode culling = nvrhi::RasterCullMode::Back;
        ColorMask colorMask = ColorMask::All;
    };

    struct MaterialBlendSettings {
        // TODO: add blending settings
    };

    struct MaterialDepthSettings {
        bool testEnabled;
        bool writeEnabled;
        nvrhi::ComparisonFunc comparison;

        static constexpr MaterialDepthSettings Opaque() {
            return MaterialDepthSettings{ true, true, nvrhi::ComparisonFunc::LessOrEqual };
        }
        static constexpr MaterialDepthSettings Transparent() {
            return MaterialDepthSettings{ true, false, nvrhi::ComparisonFunc::LessOrEqual };
        }
    };

    struct MaterialStencilSettings {
        bool enabled = false;
        nvrhi::DepthStencilState::StencilOpDesc front;
        nvrhi::DepthStencilState::StencilOpDesc back;
    };

    class Material : public Resource {
        private:
        std::shared_ptr<Shader> vertexShader;
        std::shared_ptr<Shader> geometryShader;
        std::shared_ptr<Shader> pixelShader;

        nvrhi::BindingSetHandle vertexBindings;
        nvrhi::BindingSetHandle geometryBindings;
        nvrhi::BindingSetHandle pixelBindings;

        // TODO: shaders can only have resource properties for now. change later
        std::vector<nvrhi::IResource*> vertexResources;
        std::vector<nvrhi::IResource*> geometryResources;
        std::vector<nvrhi::IResource*> pixelResources;
        bool resourcesDirty;

        MaterialDrawSettings drawSettings;
        MaterialDepthSettings depthSettings;
        MaterialStencilSettings stencilSettings;
        bool settingsDirty;

        public:
        Material() = default;

        static constexpr Material Opaque() {
            auto material = Material();
            material.depthSettings = MaterialDepthSettings::Opaque();
            return material;
        }

        static constexpr Material Transparent() {
            auto material = Material();
            material.depthSettings = MaterialDepthSettings::Transparent();
            return material;
        }

        nvrhi::BindingSetVector GetGPUBindings() const {
            nvrhi::BindingSetVector bindings;
            if (vertexBindings) bindings.push_back(vertexBindings);
            if (geometryBindings) bindings.push_back(geometryBindings);
            if (pixelBindings) bindings.push_back(pixelBindings);
            return bindings;
        }

        std::shared_ptr<Shader> GetVertexShader() const { return vertexShader; }
        std::shared_ptr<Shader> GetGeometryShader() const { return geometryShader; }
        std::shared_ptr<Shader> GetPixelShader() const { return pixelShader; }

        const MaterialDrawSettings& GetDrawSettings() const { return drawSettings; }
        const MaterialDepthSettings& GetDepthSettings() const { return depthSettings; }
        const MaterialStencilSettings& GetStencilSettings() const { return stencilSettings; }

        bool IsValid() const override { return vertexShader && pixelShader; }
        bool IsSettingsDirty() const { return settingsDirty; }

        #define SHADER_SET(type) \
        if (type##Shader != shader) { \
            type##Resources.clear(); \
        } \
        type##Shader = shader; \
        type##Resources.resize(shader->GetProperties().size()); \
        resourcesDirty = true; \

        void SetVertexShader(const std::shared_ptr<Shader>& shader) {
            SHADER_SET(vertex)
        }
        void SetGeometryShader(const std::shared_ptr<Shader>& shader) {
            SHADER_SET(geometry)
        }
        void SetPixelShader(const std::shared_ptr<Shader>& shader) {
            SHADER_SET(pixel)
        }

        #undef SHADER_SET

        void SetDrawSettings(const MaterialDrawSettings& drawSettings) {
            this->drawSettings = drawSettings;
            settingsDirty = true;
        }
        void SetDepthSettings(const MaterialDepthSettings& depthSettings) {
            this->depthSettings = depthSettings;
            settingsDirty = true;
        }
        void SetStencilSettings(const MaterialStencilSettings& stencilSettings) {
            this->stencilSettings = stencilSettings;
            settingsDirty = true;
        }

        bool SetProperty(const std::string& property, const std::shared_ptr<Texture>& texture);
        bool SetProperty(const std::string& property, const nvrhi::SamplerHandle& sampler);

        bool UpdateBindings();
        nvrhi::GraphicsPipelineDesc GetGPUPipelineDesc() const;
    };
}
