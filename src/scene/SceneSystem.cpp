//
// Created by ryen on 12/6/24.
//

#include <cstdint>

#include "SceneSystem.h"

namespace me::scene {
    bool Initialize() {
        nextId = 0;
        initialized = true;
        return true;
    }

    void AddScene(const ScenePtr scene) {
        scene->Internal_StartManage(GetNextId());
        scenes.insert({ scene->GetID(), scene });
    }

    void Deinitialize() {

    }

    uint32_t GetNextId() {
        return ++nextId;
    }
}
