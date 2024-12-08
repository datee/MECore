//
// Created by ryen on 12/5/24.
//

#ifndef SCENECAMERA_H
#define SCENECAMERA_H

#include "../../math/Types.h"
#include "SceneObject.h"

namespace me::scene {
    // Remember: FOV is vertical
    class SceneCamera : public SceneObject {
        private:
        // Vertical field of view.
        float fieldOfView = 60.0f;
        float zNear = 0.01f;
        float zFar = 1000.0f;

        bool usingCustomProjection;
        math::Matrix4x4 projection;

        // Regenerates the projection matrix using this camera's FOV.
        void RegenerateMatrix();

        public:
        SceneCamera();

        inline void SetFOV(float fov) { fieldOfView = fov; RegenerateMatrix(); }
        [[nodiscard]] inline float GetFOV() const { return fieldOfView; }
    };
}

#endif //SCENECAMERA_H
