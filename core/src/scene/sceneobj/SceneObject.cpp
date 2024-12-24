//
// Created by ryen on 12/5/24.
//

#include "SceneObject.h"

namespace me::scene {
    SceneObject::SceneObject() : SceneObject("") {

    }

    SceneObject::SceneObject(const std::string str) {
        world = nullptr;
        enabled = true;
        transform = SceneTransform();
        name = str;
    }

    SceneObject::~SceneObject() {

    }

    void SceneObject::Internal_AssignWorld(SceneWorld *world) {
        this->world = world;
    }
}
