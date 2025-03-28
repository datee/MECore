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
        worldBuffer = device->createBuffer(nvrhi::utils::CreateVolatileConstantBufferDesc(sizeof(WorldData), "WorldData", 8));
        // worldBuffer = device->createBuffer(nvrhi::BufferDesc()
        //     .setByteSize(sizeof(WorldData))
        //     .setIsConstantBuffer(true)
        //     .setIsVolatile(true)
        //     .setMaxVersions(16)
        //     // .setInitialState(nvrhi::ResourceStates::CopyDest)
        //     // .setKeepInitialState(true)
        //     .setDebugName("WorldBuffer"));

        CreateGlobalBindingLayout();
        CreateGlobalBindingSet();
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

        auto worldData = WorldData();
        camera->GetTransform().ToInverseTRS().StoreFloat4x4(worldData.view);
        camera->GetProjectionMatrix().StoreFloat4x4(worldData.projection);
        commandList->writeBuffer(worldBuffer, &worldData, sizeof(WorldData));

        nvrhi::utils::ClearColorAttachment(commandList, framebuffer, 0, nvrhi::Color(0.2f));

        commandList->beginMarker("Meshes");

        for (auto model : node->GetModels()) {
            if (!model->IsEnabled()) continue;
            if (model->model == nullptr) continue;

            model->model->UploadBuffers(commandList);
            auto objectData = ObjectData();
            model->GetTransform().ToTRS().StoreFloat4x4(objectData.transform);

            for (int meshIndex = 0; meshIndex < model->model->meshes.size(); meshIndex++) {
                auto mesh = model->model->meshes[meshIndex];
                auto material = model->model->materials[meshIndex];

                if (!material->GetPipeline()) {
                    material->CreateGPUPipeline(framebuffer);
                }

                nvrhi::GraphicsState graphicsState = nvrhi::GraphicsState()
                    .setPipeline(material->GetPipeline())
                    .setFramebuffer(framebuffer)
                    .setViewport(nvrhi::ViewportState().addViewportAndScissorRect(nvrhi::Viewport(bufferWidth, bufferHeight)))
                    .addBindingSet(globalBindingSet);

                auto attrCount = material->vertexShader->GetInputLayout()->getNumAttributes();
                for (int attrIndex = 0; attrIndex < attrCount; attrIndex++) {
                    auto attr = material->vertexShader->GetInputLayout()->getAttributeDesc(attrIndex);
                    auto buffer = mesh->GetBufferBySemantic(attr->name);
                    if (buffer == nullptr) continue;

                    graphicsState.addVertexBuffer(nvrhi::VertexBufferBinding().setBuffer(buffer).setSlot(attr->bufferIndex));
                }

                if (auto indexStream = mesh->GetIndexStream(); indexStream != nullptr) {
                    graphicsState.setIndexBuffer(nvrhi::IndexBufferBinding().setBuffer(mesh->GetIndexBuffer()).setFormat(indexStream->GetFormat()));

                    nvrhi::DrawArguments drawArgs;
                    drawArgs.vertexCount = indexStream->GetCount();
                    drawArgs.startVertexLocation = 0;
                    drawArgs.startIndexLocation = 0;

                    commandList->setGraphicsState(graphicsState);
                    commandList->setPushConstants(&objectData, sizeof(objectData));
                    commandList->drawIndexed(drawArgs);
                } else {
                    nvrhi::DrawArguments drawArgs;
                    drawArgs.vertexCount = mesh->GetPositionStream()->GetCount();
                    drawArgs.startVertexLocation = 0;

                    commandList->setGraphicsState(graphicsState);
                    commandList->setPushConstants(&objectData, sizeof(objectData));
                    commandList->draw(drawArgs);
                }
            }
        }

        commandList->endMarker();
        commandList->close();

        RenderInterface::instance->GetDevice()->executeCommandList(commandList);
    }

    void ExamplePipeline::CreateGlobalBindingLayout() {
        auto device = RenderInterface::instance->GetDevice();

        auto layoutDesc = nvrhi::BindingLayoutDesc()
        .setVisibility(nvrhi::ShaderType::All)
        .setRegisterSpace(0)
        .setRegisterSpaceIsDescriptorSet(true)
        .setBindingOffsets({ 0, 0, 0, 0 }) // you caused me a lot of issues
        .addItem(nvrhi::BindingLayoutItem::VolatileConstantBuffer(0))
        .addItem(nvrhi::BindingLayoutItem::PushConstants(1, sizeof(ObjectData)));

        globalBindingLayout = device->createBindingLayout(layoutDesc);
    }

    void ExamplePipeline::CreateGlobalBindingSet() {
        auto device = RenderInterface::instance->GetDevice();

        auto setDesc = nvrhi::BindingSetDesc()
        .setTrackLiveness(false)
        .addItem(nvrhi::BindingSetItem::ConstantBuffer(0, worldBuffer))
        .addItem(nvrhi::BindingSetItem::PushConstants(1, sizeof(ObjectData)));

        globalBindingSet = device->createBindingSet(setDesc, globalBindingLayout);
    }
}
