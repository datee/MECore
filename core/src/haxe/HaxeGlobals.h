//
// Created by ryen on 12/29/24.
//

#ifndef HAXEGLOBALS_H
#define HAXEGLOBALS_H
#include "HaxeSystem.h"

namespace me::haxe {
    inline std::unique_ptr<HaxeSystem> mainSystem;

    void Initialize(int argc, void** argv);
    void Shutdown();

    // Helper function to create the main Haxe system. Uses ME's filesystem.
    bool CreateMainSystem(const std::string& path);
}

#endif //HAXEGLOBALS_H
