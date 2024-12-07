//
// Created by ryen on 12/4/24.
//

#include <memory>
#include "Scene.h"

namespace me::scene {
    Scene::Scene() {
        isManaged = false;
        id = 0;
    }

    void Scene::Internal_StartManage(uint32_t id) {
        isManaged = true;
        this->id = id;
    }

    void Scene::Internal_StopManage() {
        isManaged = false;
        id = 0;
    }
}
