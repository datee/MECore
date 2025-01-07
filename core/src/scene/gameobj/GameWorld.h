//
// Created by ryen on 12/22/24.
//

#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include <memory>
#include <vector>

#include "GameObject.h"

namespace me::scene {
    using GameWorldList = std::vector<std::unique_ptr<GameObject>>;

    class GameWorld final : public haxe::HaxeEngineObject {
        private:
        GameWorldList objects; // TODO: figure out game object ids and change this to a map

        public:
        GameWorld();

        [[nodiscard]] std::vector<GameObject*> GetObjects();

        void Update();
        void FixedUpdate();
        void LateUpdate();

        void AddObject(GameObject* obj);
    };
}

#endif //GAMEWORLD_H
