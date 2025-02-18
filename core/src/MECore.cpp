//
// Created by ryen on 12/29/24.
//

#include "MECore.h"

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

#include "haxe/HaxeGlobals.h"
#include "log/LogSystem.h"
#include "physics/PhysicsGlobals.h"
#include "render/RenderGlobals.h"
#include "scene/SceneGlobals.h"
#include "time/TimeGlobal.h"

namespace me {
    static MECoreSystems initialized;

    inline bool Has(MECoreSystems value, MECoreSystems flags) {
        int v = static_cast<int>(value);
        int f = static_cast<int>(flags);
        return (v & f) == f;
    }

    bool Core_Initialize(const MECoreSystems& systems) {
        if (Has(systems, MECoreSystems::Log)) {
            log::Initialize();
        }
        if (Has(systems, MECoreSystems::Haxe)) {
            haxe::Initialize(0, nullptr);
            haxe::CreateMainSystem("/code.hl");
        }
        if (Has(systems, MECoreSystems::SDLRender)) {
            if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
                spdlog::critical("Failed to initialize SDL video subsystem");
                return false;
            }
            render::Initialize();
        }
        if (Has(systems, MECoreSystems::Physics)) {
            physics::Initialize();
        }
        if (Has(systems, MECoreSystems::Scene)) {
            scene::Initialize();
        }
        if (Has(systems, MECoreSystems::Time)) {
            time::Initialize();
        }

        initialized = systems;
        return true;
    }

    void Core_Shutdown() {
        if (Has(initialized, MECoreSystems::Scene)) {
            scene::Shutdown();
        }
        if (Has(initialized, MECoreSystems::Physics)) {
            physics::Shutdown();
        }
        if (Has(initialized, MECoreSystems::SDLRender)) {
            render::Shutdown();
            SDL_QuitSubSystem(SDL_INIT_VIDEO);
        }
        if (Has(initialized, MECoreSystems::Haxe)) {
            haxe::Shutdown();
        }

        SDL_Quit();
    }
}
