//
// Created by ryen on 12/29/24.
//

#include "SceneGlobals.h"

namespace me::scene {
    void Initialize() {
        mainSystem = std::make_unique<SceneSystem>();
    }

    void Shutdown() {
        mainSystem = nullptr;
    }
}
