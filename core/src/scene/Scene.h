//
// Created by ryen on 12/4/24.
//

#ifndef SCENE_H
#define SCENE_H

#include "sceneobj/SceneWorld.h"

namespace me::scene {
    // Holds all kinds of objects for game.
    class Scene {
        private:
        bool isManaged;
        uint32_t id;
        SceneWorld sceneWorld;

        public:
        Scene();

        [[nodiscard]] inline uint32_t GetID() const { return id; }
        [[nodiscard]] inline SceneWorld& GetSceneWorld() { return sceneWorld; }

        void Internal_StartManage(uint32_t id);
        void Internal_StopManage();

        void Update();
    };

    typedef std::shared_ptr<Scene> ScenePtr;
}

#endif //SCENE_H
