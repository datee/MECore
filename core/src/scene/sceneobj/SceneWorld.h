//
// Created by ryen on 12/5/24.
//

#ifndef SCENEWORLD_H
#define SCENEWORLD_H

#include <vector>
#include <memory>
#include <map>

#include "SceneObject.h"
#include "SceneCamera.h"

namespace me::scene {
    using SceneWorldMap = std::map<uint32_t, std::unique_ptr<SceneObject>>;
    using SceneWorldList = std::vector<std::unique_ptr<SceneObject>>;

    class SceneWorld {
        private:
        SceneWorldList objects;
        SceneCamera camera;

        public:
        SceneWorld();

        [[nodiscard]] inline SceneCamera& GetCamera() { return camera; }
        [[nodiscard]] std::vector<SceneObject*> GetSceneObjects();

        void AddObject(SceneObject* obj);
    };
}

#endif //SCENEWORLD_H
