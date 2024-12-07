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
        SceneWorld* world; // no good use of a smart pointer here
        bool enabled;
        math::Transform transform;

        public:
        SceneObject();

        [[nodiscard]] inline bool IsEnabled() const;
        inline void SetEnabled(bool state);
        [[nodiscard]] math::Transform& GetTransform();

        void Internal_AssignWorld(SceneWorld* world);
    };

    typedef std::shared_ptr<SceneObject> SceneObjectPtr;
}

#endif //SCENEOBJECT_H
