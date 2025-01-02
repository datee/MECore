//
// Created by ryen on 12/22/24.
//

#ifndef GAMEOBJECTMODULE_H
#define GAMEOBJECTMODULE_H
#include "haxe/HaxeEngineObject.h"

namespace me::scene {
    class GameObject;

    class GameObjectModule : public haxe::HaxeEngineObject {
        protected:
        GameObject* gameObject = nullptr;

        explicit GameObjectModule(GameObject* obj, const haxe::TypeName& typeName);
    };
}

#endif //GAMEOBJECTMODULE_H
