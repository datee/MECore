//
// Created by ryen on 12/29/24.
//

#pragma once

#include <spdlog/spdlog.h>

#include "math/Types.h"
#include "math/Transform.h"
#include "fs/FileSystem.h"

// Platform defines derived from WickedEngine. Thank you turanszkij.
// WickedEngine is licensed under the MIT license.

#ifdef _WIN32
    #if WINAPI_FAMILY == WINAPI_FAMILY_GAMES
        #define PLATFORM_XBOX
    #else
        #define PLATFORM_WINDOWS
    #endif
#elif defined(__SCE__)
    #define PLATFORM_PS5
#else
    #define PLATFORM_LINUX
#endif

namespace ME {
    struct MEAppData {
        std::string name;
        std::string company;
        std::string version;
    };

    enum class MECoreSystems {
        None = 0,
        Input = 1,
        Filesystem = Input << 1,
        Haxe = Filesystem << 1,
        Physics = Haxe << 1,
        Time = Physics << 1,
        Render = Physics << 1,

        All = ~0,
    };

    inline MEAppData appData;

    // Initializes specified engine subsystems
    bool Core_Initialize(const MECoreSystems& systems = MECoreSystems::All);
    void Core_Shutdown();
}
