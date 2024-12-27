//
// Created by ryen on 12/6/24.
//

#include <cstdint>

#include "SceneSystem.h"

namespace me::scene {
    SceneSystem::SceneSystem() {
        scenes = SceneMap();
        nextId = 0;
    }

    void SceneSystem::AddScene(const ScenePtr scene) {
        scene->Internal_StartManage(GetNextId());
        scenes.insert({ scene->GetID(), scene });
    }

    void SceneSystem::RemoveScene(ScenePtr scene) {

    }

    void SceneSystem::NewFrame() {

    }

    uint32_t SceneSystem::GetNextId() {
        return ++nextId;
    }
}
