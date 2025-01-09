//
// Created by ryen on 12/4/24.
//

#include <memory>
#include "Scene.h"

namespace me::scene {
    Scene::Scene() : HaxeEngineObject(u"me.Scene"), sceneWorld(this), physicsWorld(60), gameWorld(this) {
        isManaged = false;
        id = 0;

        object->SetPtr("SceneWorld", sceneWorld.GetHaxeObject()->GetDynamic());
        object->SetPtr("GameWorld", gameWorld.GetHaxeObject()->GetDynamic());
    }

    void Scene::Update() {
        gameWorld.StartCheck();
        gameWorld.Update();

        if (physicsWorld.CanUpdate()) {
            gameWorld.FixedUpdate();
            physicsWorld.TryUpdate();
        }

        // Scene world update here
        gameWorld.LateUpdate();
    }

    void Scene::PreRender() {
        gameWorld.OnPreRender();
    }

    void Scene::Internal_StartManage(uint32_t id) {
        isManaged = true;
        this->id = id;
    }

    void Scene::Internal_StopManage() {
        isManaged = false;
        id = 0;
    }
}
