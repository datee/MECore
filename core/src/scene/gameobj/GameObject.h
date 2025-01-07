//
// Created by ryen on 12/22/24.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "GameComponentManager.h"
#include "GameTransform.h"
#include "haxe/HaxeEngineObject.h"

namespace me::scene {
    class GameWorld;

    class GameObject final : public haxe::HaxeEngineObject {
        private:
        GameWorld* world;
        GameObject* parent;
        GameTransform transform;
        GameComponentManager components;
        std::string name;

        public:
        GameObject();
        explicit GameObject(const std::string& name);
        explicit GameObject(GameObject* parent);

        [[nodiscard]] inline GameObject* GetParent() const { return parent; }
        [[nodiscard]] inline GameTransform& GetTransform() { return transform; }
        [[nodiscard]] inline GameComponentManager& GetComponents() { return components; }
        [[nodiscard]] inline std::string GetName() const { return name; }

        inline void SetParent(GameObject* parent) { this->parent = parent; }

        void Internal_AssignWorld(GameWorld* world);
    };
}

#endif //GAMEOBJECT_H
