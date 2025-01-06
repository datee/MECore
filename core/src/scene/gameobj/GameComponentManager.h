//
// Created by ryen on 1/1/25.
//

#ifndef GAMECOMPONENTMANAGER_H
#define GAMECOMPONENTMANAGER_H
#include "GameObjectModule.h"

namespace me::scene {
    class GameComponentManager : public GameObjectModule {
        public:
        void CreateComponent(haxe::HaxeType* type);
    };
}

#endif //GAMECOMPONENTMANAGER_H
