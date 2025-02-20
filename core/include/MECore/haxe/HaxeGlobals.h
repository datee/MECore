//
// Created by ryen on 12/29/24.
//

#pragma once

#include "HaxeSystem.h"

namespace ME::haxe {
    inline std::unique_ptr<HaxeSystem> mainSystem;

    void Initialize(int argc, void** argv);
    void Shutdown();
}
