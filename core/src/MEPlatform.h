//
// Created by ryen on 12/30/24.
//

#ifndef MEPLATFORM_H
#define MEPLATFORM_H

// Derived from WickedEngine. Thank you turanszkij.
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

#endif //MEPLATFORM_H
