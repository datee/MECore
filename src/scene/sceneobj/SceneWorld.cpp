//
// Created by ryen on 12/6/24.
//

#include "SceneWorld.h"

namespace me::scene {
    SceneWorld::SceneWorld() {
        AddObject(&camera);
    }

    void SceneWorld::AddObject(SceneObject* obj) {
        obj->Internal_AssignWorld(this);
        allSceneObjects.insert({ allSceneObjects.size(), std::unique_ptr<SceneObject>(obj) });
    }

}
