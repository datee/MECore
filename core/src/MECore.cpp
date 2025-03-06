//
// Created by ryen on 12/29/24.
//

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

#include "MECore/MECore.h"
#include "MECore/haxe/HaxeSystem.h"
#include "MECore/physics/PhysicsGlobals.h"
#include "MECore/time/TimeGlobal.h"
#include "MECore/filesystem/FileSystem.h"

namespace ME {
    static MECoreSystems initialized;

    inline bool Has(MECoreSystems value, MECoreSystems flags) {
        int v = static_cast<int>(value);
        int f = static_cast<int>(flags);
        return (v & f) == f;
    }

    bool Core_Initialize(const MECoreSystems& systems) {
        if (Has(systems, MECoreSystems::Filesystem)) {
            filesystem::Initialize();
        }
        if (Has(systems, MECoreSystems::Haxe)) {
            haxe::Initialize(0, nullptr);
        }
        if (Has(systems, MECoreSystems::Physics)) {
            physics::Initialize();
        }
        if (Has(systems, MECoreSystems::Time)) {
            time::Initialize();
        }
        if (Has(systems, MECoreSystems::Render)) {
            SDL_InitSubSystem(SDL_INIT_VIDEO);
        }

        initialized = systems;
        return true;
    }

    void Core_Shutdown() {
        if (Has(initialized, MECoreSystems::Render)) {
            SDL_QuitSubSystem(SDL_INIT_VIDEO);
        }
        if (Has(initialized, MECoreSystems::Physics)) {
            physics::Shutdown();
        }
        if (Has(initialized, MECoreSystems::Haxe)) {
            haxe::Shutdown();
        }
        if (Has(initialized, MECoreSystems::Filesystem)) {
            filesystem::Shutdown();
        }

        SDL_Quit();
    }
}
