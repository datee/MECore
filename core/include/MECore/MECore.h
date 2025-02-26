//
// Created by ryen on 12/29/24.
//

#pragma once

#include <spdlog/spdlog.h>

#include "math/Types.h"
#include "math/Transform.h"

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
    enum class MECoreSystems {
        None = 0,
        Input = 1,
        Haxe = Input << 1,
        Physics = Haxe << 1,
        Time = Physics << 1,

        All =  Physics | Time | Haxe | Input,
    };

    // Initializes specified engine subsystems
    bool Core_Initialize(const MECoreSystems& systems);
    void Core_Shutdown();
}
