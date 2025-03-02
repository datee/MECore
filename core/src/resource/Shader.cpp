//
// Created by ryen on 3/1/25.
//

#include "MECore/resource/Shader.h"
#include "MECore/render/RenderInterface.h"

namespace ME::resource {
    bool Shader::CreateGPUShader() {
        auto nvDevice = render::RenderInterface::instance->GetDevice();

        auto desc = nvrhi::ShaderDesc(type);
        shader = nvDevice->createShader(desc, bytecode.data(), bytecode.size());
        bindingLayout = nvDevice->createBindingLayout(bindings);

        if (type == nvrhi::ShaderType::Vertex) {
            inputLayout = nvDevice->createInputLayout(vertexAttributes.data(), vertexAttributes.size(), shader);
        }

        return shader && bindingLayout;
    }

}
