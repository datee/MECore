//
// Created by ryen on 12/29/24.
//

#include "MECore.h"

#include <SDL3/SDL.h>

#include "fs/FileSystem.h"
#include "haxe/HaxeGlobals.h"
#include "job/JobGlobals.h"
#include "log/LogSystem.h"
#include "physics/PhysicsGlobals.h"
#include "render/RenderGlobals.h"
#include "scene/SceneGlobals.h"
#include "spdlog/spdlog.h"
#include "time/TimeGlobal.h"

namespace me {
    static MESystems initialized;

    inline bool Has(MESystems value, MESystems flags) {
        int v = static_cast<int>(value);
        int f = static_cast<int>(flags);
        return (v & f) == f;
    }

    bool Initialize(const MESystems& systems) {
        if (Has(systems, MESystems::Log)) {
            log::Initialize();
        }
        if (Has(systems, MESystems::SDLRender)) {
            if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
                spdlog::critical("Failed to initialize SDL video subsystem");
                return false;
            }
            render::Initialize();
        }
        if (Has(systems, MESystems::Haxe)) {
            haxe::Initialize(0, nullptr);
        }
        if (Has(systems, MESystems::Job)) {
            job::Initialize();
        }
        if (Has(systems, MESystems::Physics)) {
            physics::Initialize();
        }
        if (Has(systems, MESystems::FS)) {
            fs::Initialize();
        }
        if (Has(systems, MESystems::Scene)) {
            scene::Initialize();
        }
        if (Has(systems, MESystems::Time)) {
            time::Initialize();
        }

        initialized = systems;
        return true;
    }

    void Shutdown() {
        if (Has(initialized, MESystems::Scene)) {
            scene::Shutdown();
        }
        if (Has(initialized, MESystems::Physics)) {
            physics::Shutdown();
        }
        if (Has(initialized, MESystems::Job)) {
            job::Shutdown();
        }
        if (Has(initialized, MESystems::Haxe)) {
            haxe::Shutdown();
        }
        if (Has(initialized, MESystems::SDLRender)) {
            render::Shutdown();
            SDL_QuitSubSystem(SDL_INIT_VIDEO);
        }

        SDL_Quit();
    }
}
