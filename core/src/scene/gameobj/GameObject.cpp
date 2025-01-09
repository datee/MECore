//
// Created by ryen on 12/22/24.
//

#include "GameObject.h"

#include "GameWorld.h"
#include "scene/Scene.h"

namespace me::scene {
    GameObject::GameObject() : HaxeEngineObject(u"me.game.GameObject"), transform(this), components(this) {
        world = nullptr;
        parent = nullptr;
        object->SetPtr("Transform", transform.GetHaxeObject());
        object->SetPtr("Components", components.GetHaxeObject());
    }

    GameObject::GameObject(GameObject* parent) : GameObject() {
        SetParent(parent);
    }

    GameObject::GameObject(const std::string& name) : GameObject() {
        this->name = name;
    }

    void GameObject::SetParent(GameObject* parent) {
        this->parent = parent;
        object->SetPtr("Parent", parent->GetHaxeObject());
    }

    void GameObject::Internal_AssignWorld(GameWorld* world) {
        this->world = world;
        object->SetPtr("Scene", world->GetScene()->GetHaxeObject());
    }
}
