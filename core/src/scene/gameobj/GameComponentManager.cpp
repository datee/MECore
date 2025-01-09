//
// Created by ryen on 1/1/25.
//

#include "GameComponentManager.h"

#include "haxe/HaxeType.h"

namespace me::scene {
    GameComponentManager::GameComponentManager(GameObject* obj) : GameObjectModule(obj, u"me.game.ComponentManager") {

    }

    void GameComponentManager::StartCheck() const {
        object->CallMethod(u"ME_StartCheck", {});
    }

    void GameComponentManager::Update() const {
        object->CallMethod(u"ME_Update", {});
    }

    void GameComponentManager::FixedUpdate() const {
        object->CallMethod(u"ME_FixedUpdate", {});
    }

    void GameComponentManager::LateUpdate() const {
        object->CallMethod(u"ME_LateUpdate", {});
    }

    void GameComponentManager::OnPreRender() const {
        object->CallMethod(u"ME_PreRender", {});
    }

    void GameComponentManager::CreateComponent(haxe::HaxeType* type) const {
        hl_type hlType;
        hlType.kind = HTYPE;
        hlType.tparam = type->GetType();

        vdynamic typeArg{};
        typeArg.t = &hlType;
        typeArg.v.ptr = type->GetType();

        object->CallMethod(u"ME_CreateComponent", { &typeArg });
    }

}
