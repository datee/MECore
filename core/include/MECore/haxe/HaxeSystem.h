//
// Created by ryen on 12/29/24.
//

#pragma once

#include "HaxeModule.h"

namespace ME::haxe {
    inline std::shared_ptr<HaxeModule> mainSystem;

    void Initialize(int argc, void** argv);
    void Shutdown();
}
