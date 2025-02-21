//
// Created by ryen on 12/29/24.
//

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

#include "MECore/MECore.h"
#include "MECore/haxe/HaxeGlobals.h"
#include "MECore/log/LogSystem.h"
#include "MECore/physics/PhysicsGlobals.h"
#include "MECore/render/RenderGlobals.h"
#include "MECore/time/TimeGlobal.h"

namespace ME {
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
        }
        if (Has(systems, MECoreSystems::Render)) {
            render::Initialize();
        }
        if (Has(systems, MECoreSystems::Physics)) {
            physics::Initialize();
        }
        if (Has(systems, MECoreSystems::Time)) {
            time::Initialize();
        }

        initialized = systems;
        return true;
    }

    void Core_Shutdown() {
        if (Has(initialized, MECoreSystems::Physics)) {
            physics::Shutdown();
        }
        if (Has(initialized, MECoreSystems::Render)) {
            render::Shutdown();
            SDL_QuitSubSystem(SDL_INIT_VIDEO);
        }
        if (Has(initialized, MECoreSystems::Haxe)) {
            haxe::Shutdown();
        }

        SDL_Quit();
    }
}
