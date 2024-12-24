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
    typedef std::map<uint32_t, std::unique_ptr<SceneObject>> WorldMap;
    typedef std::vector<std::unique_ptr<SceneObject>> WorldList;

    class SceneWorld {
        private:
        WorldList objects;
        SceneCamera camera;

        public:
        SceneWorld();

        [[nodiscard]] inline SceneCamera& GetCamera() { return camera; }
        [[nodiscard]] std::vector<SceneObject*> GetSceneObjects();

        void AddObject(SceneObject* obj);
    };
}

#endif //SCENEWORLD_H
