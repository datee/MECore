#include <nvrhi/utils.h>

#include "MECore/MECore.h"
#include "MECore/render/RenderTarget.h"
#include "MECore/render/pipeline/ExamplePipeline.h"

namespace ME::render {
    struct WorldData {
        PackedMatrix4x4 view;
        PackedMatrix4x4 projection;
    };

    struct ObjectData {
        PackedMatrix4x4 transform;
    };

    ExamplePipeline::ExamplePipeline() {
        auto device = RenderInterface::instance->GetDevice();
        commandList = device->createCommandList();
        worldBuffer = device->createBuffer(nvrhi::BufferDesc()
        .setByteSize(sizeof(WorldData))
        .setIsConstantBuffer(true)
        .setIsVolatile(true)
        .setMaxVersions(16));
    }

    void ExamplePipeline::AddPass(RenderPass* pass, RenderStage stage, int order) {
        // do nothing
    }

    void ExamplePipeline::Render(const node::RenderRootNode* node, node::RenderCamera* camera) {
        auto target = RenderTarget::current;
        auto framebuffer = target->GetFramebuffer();
        
        int bufferWidth, bufferHeight;
        target->GetSize(&bufferWidth, &bufferHeight);

        commandList->open();

        nvrhi::utils::ClearColorAttachment(commandList, framebuffer, 0, nvrhi::Color(0.2f));

        auto worldData = WorldData();
        camera->GetTransform().ToTRS().StoreFloat4x4(worldData.view);
        camera->GetProjectionMatrix().StoreFloat4x4(worldData.projection);
        commandList->writeBuffer(worldBuffer, &worldData, sizeof(WorldData));

        commandList->beginMarker("Meshes");

        for (auto model : node->GetModels()) {
            model->model->TryAddUpload(commandList);
            auto objectData = ObjectData();
            model->GetTransform().ToTRS().StoreFloat4x4(objectData.transform);

            for (int i = 0; i < model->model->meshes.size(); i++) {
                auto mesh = model->model->meshes[i];
                auto material = model->model->materials[i];

                if (!material->GetPipeline()) {
                    material->CreateGPUPipeline(framebuffer);
                }

                nvrhi::GraphicsState graphicsState = nvrhi::GraphicsState()
                    .setPipeline(material->GetPipeline())
                    .setFramebuffer(framebuffer)
                    .setViewport(nvrhi::ViewportState().addViewportAndScissorRect(nvrhi::Viewport(bufferWidth, bufferHeight)))
                    .addVertexBuffer(nvrhi::VertexBufferBinding().setBuffer(mesh->GetVertexBuffer()))
                    .setIndexBuffer(nvrhi::IndexBufferBinding().setBuffer(mesh->GetIndexBuffer()).setFormat(nvrhi::Format::R32_UINT));
                
                graphicsState.bindings = material->GetBindings();

                nvrhi::DrawArguments drawArgs;
                drawArgs.vertexCount = mesh->vertices.size();
                drawArgs.startVertexLocation = 0;
                drawArgs.startIndexLocation = 0;

                commandList->setGraphicsState(graphicsState);
                commandList->setPushConstants(&objectData, sizeof(objectData));
                commandList->drawIndexed(drawArgs);
            }
        }

        commandList->endMarker();
        commandList->close();

        RenderInterface::instance->GetDevice()->executeCommandList(commandList);
    }
}
