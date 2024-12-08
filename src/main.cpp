//
// Created by ryen on 12/4/24.
//

#define SDL_MAIN_USE_CALLBACKS

#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "render/MainWindow.h"
#include "scene/SceneSystem.h"

struct AppContext {
    me::scene::ScenePtr scene;
    me::scene::SceneObject* object;

    bool shouldQuit;
};

SDL_AppResult SDL_Fail() {
    SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "SDL Error: %s", SDL_GetError());
    return SDL_APP_FAILURE;
}

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return SDL_Fail();
    }

    me::window::OpenWindow("MANIFOLDEngine", { 1280, 720 });

    auto ctx = new AppContext();

    ctx->shouldQuit = false;
    ctx->scene = std::make_shared<me::scene::Scene>();
    ctx->object = new me::scene::SceneObject();

    ctx->scene->GetSceneWorld().AddObject(ctx->object);
    ctx->scene->GetSceneWorld().GetCamera().GetTransform().position = { 0.f, 0.f, -10.f };

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

    // render stuff????

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
