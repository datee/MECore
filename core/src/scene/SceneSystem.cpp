//
// Created by ryen on 12/6/24.
//

#include <cstdint>

#include "SceneSystem.h"

namespace me::scene {
    SceneSystem::SceneSystem() : HaxeEngineObject(u"me.SceneSystem") {
        scenes = SceneMap();
        nextId = 0;
    }

    void SceneSystem::AddScene(const ScenePtr scene) {
        scene->Internal_StartManage(GetNextId());
        scenes.insert({ scene->GetID(), scene });
    }

    void SceneSystem::RemoveScene(ScenePtr scene) {

    }

    void SceneSystem::Update() const {
        for (const auto& pair : scenes) {
            pair.second->Update();
        }
    }

    void SceneSystem::PreRender() const {
        for (const auto& pair : scenes) {
            pair.second->PreRender();
        }
    }

    uint32_t SceneSystem::GetSceneCount() const {
        return scenes.size();
    }

    ScenePtr SceneSystem::GetScene(const uint32_t id) const {
        return scenes.at(id);
    }

    uint32_t SceneSystem::GetNextId() {
        return ++nextId;
    }
}
