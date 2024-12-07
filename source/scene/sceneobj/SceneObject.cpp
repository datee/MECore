//
// Created by ryen on 12/5/24.
//

#include "SceneObject.h"

namespace me::scene {
    SceneObject::SceneObject() {
        world = nullptr;
        enabled = true;
        transform = math::Transform::IDENTITY;
    }

    bool SceneObject::IsEnabled() const {
        return enabled;
    }

    void SceneObject::SetEnabled(bool state) {
        enabled = state;
    }

    math::Transform& SceneObject::GetTransform() {
        return transform;
    }

    void SceneObject::Internal_AssignWorld(SceneWorld *world) {
        this->world = world;
    }
}
