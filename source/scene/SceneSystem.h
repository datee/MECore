//
// Created by ryen on 12/6/24.
//

#ifndef SCENESYSTEM_H
#define SCENESYSTEM_H
#include <map>
#include <memory>

#include "Scene.h"

namespace me::scene {
    static std::map<uint32_t, ScenePtr> scenes;
    static uint32_t nextId = 0;
    static bool initialized = false;

    bool Initialize();
    void AddScene(ScenePtr scene);
    void RemoveScene(ScenePtr scene);
    void NewFrame();
    void Cleanup();

    uint32_t GetNextId();
}

#endif //SCENESYSTEM_H
