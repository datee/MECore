//
// Created by ryen on 12/5/24.
//

#ifndef SCENEWORLD_H
#define SCENEWORLD_H

#include <memory>
#include <map>

#include "SceneObject.h"
#include "SceneCamera.h"

namespace me::scene {
    class SceneWorld {
        private:
        std::map<uint32_t, std::unique_ptr<SceneObject>> allSceneObjects;
        SceneCamera camera;

        public:
        SceneWorld();

        [[nodiscard]] inline SceneCamera& GetCamera() { return camera; }

        void AddObject(SceneObject* obj);
    };
}

#endif //SCENEWORLD_H
