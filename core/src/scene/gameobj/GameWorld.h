//
// Created by ryen on 12/22/24.
//

#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include <memory>
#include <vector>

#include "GameObject.h"

namespace me::scene {
    class Scene;

    using GameWorldList = std::vector<std::unique_ptr<GameObject>>;

    class GameWorld final : public haxe::HaxeEngineObject {
        private:
        Scene* scene;
        GameWorldList objects; // TODO: figure out game object ids and change this to a map

        public:
        explicit GameWorld(Scene* scene);

        [[nodiscard]] inline Scene* GetScene() const { return scene; }
        [[nodiscard]] std::vector<GameObject*> GetObjects();

        void StartCheck();
        void Update();
        void FixedUpdate();
        void LateUpdate();
        void OnPreRender();

        void AddObject(GameObject* obj);
    };
}

#endif //GAMEWORLD_H
