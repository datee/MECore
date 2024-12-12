//
// Created by ryen on 12/5/24.
//

#include "SceneObject.h"

namespace me::scene {
    SceneObject::SceneObject() {
        world = nullptr;
        enabled = true;
        transform = math::Transform::identity;
    }

    SceneObject::~SceneObject() {
        // nothing to clean up lol
    }

    void SceneObject::Internal_AssignWorld(SceneWorld *world) {
        this->world = world;
    }
}
