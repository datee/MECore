//
// Created by ryen on 12/5/24.
//

#include "SceneObject.h"

#include "SceneWorld.h"
#include "scene/Scene.h"

namespace me::scene {
    SceneObject::SceneObject(const haxe::TypeName& type) : HaxeEngineObject(type) {
        world = nullptr;
        enabled = true;

        object->SetPtr("Transform", transform.GetHaxeObject());
    }

    void SceneObject::Internal_AssignWorld(SceneWorld *world) {
        this->world = world;
        object->SetPtr("Scene", world->GetScene()->GetHaxeObject());
    }
}
