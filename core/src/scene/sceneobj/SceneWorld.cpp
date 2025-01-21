//
// Created by ryen on 12/6/24.
//

#include "SceneWorld.h"

#include <utility>

namespace me::scene {
    SceneWorld::SceneWorld(Scene* scene) : HaxeEngineObject(u"me.scene.SceneWorld") {
        this->scene = scene;
        AddObject(&camera);

        object->SetPtr("Camera", camera.GetHaxeObject());
    }

    void SceneWorld::AddObject(SceneObject* obj) {
        obj->Internal_AssignWorld(this);
        objects.push_back(std::unique_ptr<SceneObject>(obj));
        // objects.insert({ objects.size(), std::unique_ptr<SceneObject>(obj) });
    }

    std::vector<SceneObject*> SceneWorld::GetSceneObjects() {
        std::vector<SceneObject*> raw;
        raw.reserve(objects.size());
        std::ranges::transform(std::as_const(objects), std::back_inserter(raw), [](auto& ptr) { return ptr.get(); });
        return raw;
    }


}
