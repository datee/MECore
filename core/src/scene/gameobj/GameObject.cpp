//
// Created by ryen on 12/22/24.
//

#include "GameObject.h"

namespace me::scene {
    GameObject::GameObject() : HaxeEngineObject(u"me.game.GameObject"), transform(this), components(this) {
        object->SetPtr("Transform", transform.GetHaxeObject());
        object->SetPtr("Components", components.GetHaxeObject());
    }

    GameObject::GameObject(GameObject* parent) : GameObject() {
        this->parent = parent;
        object->SetPtr("Parent", parent->GetHaxeObject());
    }

    GameObject::GameObject(const std::string& name) : GameObject() {
        this->name = name;
    }

    void GameObject::Internal_AssignWorld(GameWorld* world) {
        this->world = world;
    }
}
