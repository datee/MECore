//
// Created by ryen on 12/4/24.
//

#define SDL_MAIN_USE_CALLBACKS

#include <string>
#include <tiny_gltf.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "asset/Material.h"
#include "asset/Mesh.h"
#include "asset/Shader.h"
#include "render/MainWindow.h"
#include "scene/SceneSystem.h"
#include "scene/sceneobj/SceneMesh.h"
#include "FileSystem.h"
#include "render/RenderPipeline.h"
#include "render/SimpleRenderPipeline.h"

me::math::Vector3 vertices[8] =
{
    me::math::Vector3(-1, -1, -1),
    me::math::Vector3(1, -1, -1),
    me::math::Vector3(1, 1, -1),
    me::math::Vector3(-1, 1, -1),
    me::math::Vector3(-1, -1, 1),
    me::math::Vector3(1, -1, 1),
    me::math::Vector3(1, 1, 1),
    me::math::Vector3(-1, 1, 1)
};

uint32_t indices[6 * 6] =
{
    0, 1, 3, 3, 1, 2,
    1, 5, 2, 2, 5, 6,
    5, 4, 6, 6, 4, 7,
    4, 0, 7, 7, 0, 3,
    3, 2, 7, 7, 2, 6,
    4, 5, 0, 0, 5, 1
};

struct AppContext {
    me::scene::ScenePtr scene;
    me::scene::SceneObject* exampleObject;

    me::asset::MeshPtr mesh;
    me::scene::SceneMesh* meshObject;

    me::asset::MaterialPtr material;
    me::asset::ShaderPtr vertexShader;
    me::asset::ShaderPtr fragmentShader;
    std::unique_ptr<me::render::RenderPipeline> renderPipeline;

    bool shouldQuit;
};

me::asset::ShaderPtr LoadShader(const std::string& path, me::asset::ShaderType type) {
    vfspp::IFilePtr file = me::fs::OpenFile(path);
    if (file && file->IsOpened()) {
        SDL_Log(("Opened shader: " + path).c_str());
        size_t size = file->Size();
        unsigned char* buffer = new unsigned char[size];
        memset(buffer, 0, size);
        file->Read(buffer, size);
        file->Close();

        me::asset::ShaderPtr shader = std::make_shared<me::asset::Shader>(false, type, reinterpret_cast<char*>(buffer), size);
        return shader;
    }
    SDL_Log(("Failed to load shader: " + path).c_str());
    return nullptr;
}

template <typename T>
std::vector<T> ReadAccessor(tinygltf::Model& model, int id) {
    tinygltf::Accessor accessor = model.accessors[id];

    std::vector<T> vector(accessor.count);

    tinygltf::BufferView view = model.bufferViews[accessor.bufferView];
    tinygltf::Buffer buffer = model.buffers[view.buffer];

    const size_t stride = view.byteStride / sizeof(T);
    T* dataPointer = reinterpret_cast<T*>(buffer.data.data() + view.byteOffset);
    for (size_t i = 0; i < accessor.count; i++) {
        vector[i] = dataPointer[i * stride];
    }

    return std::move(vector);
}

me::asset::MeshPtr LoadMesh(const std::string& path) {
    vfspp::IFilePtr file = me::fs::OpenFile(path);
    if (file && file->IsOpened()) {
        size_t fileSize = file->Size();
        unsigned char buffer[fileSize];
        file->Read(buffer, fileSize);
        file->Close();

        tinygltf::Model gltfModel;
        tinygltf::TinyGLTF loader;
        std::string err;
        std::string warn;

        if (loader.LoadBinaryFromMemory(&gltfModel, &err, &warn, buffer, fileSize)) {
            // assume mesh zero
            int posAccessorID = gltfModel.meshes[0].primitives[0].attributes["POSITION"];
            std::vector<me::math::Vector3> vertexBuffer = ReadAccessor<me::math::Vector3>(gltfModel, posAccessorID);

            // assume there are indices
            int indexAccessorID = gltfModel.meshes[0].primitives[0].indices;
            std::vector<unsigned int> indexBuffer = ReadAccessor<unsigned int>(gltfModel, indexAccessorID);

            return std::make_shared<me::asset::Mesh>(vertexBuffer, indexBuffer);
        }
    }
    return nullptr;
}

SDL_AppResult SDL_Fail() {
    SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "SDL Error: %s", SDL_GetError());
    return SDL_APP_FAILURE;
}

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return SDL_Fail();
    }

    me::fs::Initialize();
    me::window::OpenWindow("MANIFOLDEngine", { 1280, 720 });

    auto ctx = new AppContext();
    ctx->shouldQuit = false;

    // load shaders
    ctx->vertexShader = LoadShader("/shaders/vertex.hlsl", me::asset::ShaderType::Vertex);
    ctx->fragmentShader = LoadShader("/shaders/fragment.hlsl", me::asset::ShaderType::Fragment);
    ctx->material = std::make_shared<me::asset::Material>(ctx->vertexShader, ctx->fragmentShader);
    ctx->renderPipeline = std::make_unique<me::render::SimpleRenderPipeline>(ctx->material);

    ctx->scene = std::make_shared<me::scene::Scene>();

    // set camera pos
    ctx->scene->GetSceneWorld().GetCamera().GetTransform().position = { 0.f, 0.f, -10.f };

    // make blank object
    ctx->exampleObject = new me::scene::SceneObject();
    ctx->scene->GetSceneWorld().AddObject(ctx->exampleObject);

    // make mesh and object
    ctx->mesh = std::make_shared<me::asset::Mesh>(vertices, 8, indices, 36);
    ctx->meshObject = new me::scene::SceneMesh();
    ctx->meshObject->mesh = ctx->mesh;
    ctx->meshObject->material = ctx->material;
    ctx->scene->GetSceneWorld().AddObject(ctx->meshObject);

    me::scene::Initialize();
    me::scene::AddScene(ctx->scene);

    *appstate = ctx;
    SDL_Log("initialized");

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    auto* ctx = static_cast<AppContext*>(appstate);

    if (event->type == SDL_EVENT_QUIT) {
        ctx->shouldQuit = true;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    auto* ctx = static_cast<AppContext*>(appstate);

    ctx->renderPipeline->Render(&ctx->scene->GetSceneWorld());

    return ctx->shouldQuit ? SDL_APP_SUCCESS : SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    auto* ctx = static_cast<AppContext*>(appstate);

    if (ctx) {
        delete ctx;
    }

    me::window::CloseWindow();
    SDL_Log("Quitted");
}
