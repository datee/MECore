//
// Created by ryen on 12/22/24.
//

#include "GameObject.h"

namespace me::scene {
    GameObject::GameObject() : HaxeEngineObject(u"me.game.GameObject"), transform(this) {

    }

    GameObject::GameObject(GameObject* parent) : GameObject() {
        this->parent = parent;
    }

    GameObject::GameObject(const std::string& name) : GameObject() {
        this->name = name;
    }

    void GameObject::Internal_AssignWorld(GameWorld* world) {
        this->world = world;
    }
}
