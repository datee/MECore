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
}

#endif //HAXEGLOBALS_H
