//
// Created by ryen on 1/1/25.
//

#ifndef GAMECOMPONENTMANAGER_H
#define GAMECOMPONENTMANAGER_H
#include "GameObjectModule.h"

namespace me::scene {
    class GameComponentManager : public GameObjectModule {
        public:
        GameComponentManager(GameObject* obj);

        void StartCheck() const;
        void Update() const;
        void LateUpdate() const;
        void FixedUpdate() const;
        void OnPreRender() const;

        void CreateComponent(haxe::HaxeType* type) const;
    };
}

#endif //GAMECOMPONENTMANAGER_H
