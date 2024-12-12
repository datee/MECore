//
// Created by ryen on 12/4/24.
//

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <memory>
#include "../../math/Transform.h"

namespace me::scene {
    class SceneWorld;

    // An object used for rendering.
    class SceneObject {
        private:
        SceneWorld* world;
        bool enabled;
        math::Transform transform;

        public:
        SceneObject();
        virtual ~SceneObject();

        [[nodiscard]] inline bool IsEnabled() const { return enabled; }
        inline void SetEnabled(const bool state) { enabled = state; }
        [[nodiscard]] inline math::Transform& GetTransform() { return transform; }

        void Internal_AssignWorld(SceneWorld* world);
    };

    typedef std::shared_ptr<SceneObject> SceneObjectPtr;
}

#endif //SCENEOBJECT_H
