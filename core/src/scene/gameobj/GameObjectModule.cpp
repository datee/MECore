//
// Created by ryen on 12/22/24.
//

#include "GameObjectModule.h"

#include "GameObject.h"

namespace me::scene {
    GameObjectModule::GameObjectModule(GameObject* obj, const haxe::TypeName& typeName) : HaxeEngineObject(typeName) {
        gameObject = obj;
        object->SetPtr("GameObject", obj->GetHaxeObject());
    }

}
