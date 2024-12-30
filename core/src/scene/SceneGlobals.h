//
// Created by ryen on 12/29/24.
//

#ifndef SCENEGLOBALS_H
#define SCENEGLOBALS_H
#include "SceneSystem.h"

namespace me::scene {
    inline std::unique_ptr<SceneSystem> mainSystem;

    void Initialize();
    void Shutdown();
}

#endif //SCENEGLOBALS_H
