//
// Created by ryen on 12/5/24.
//

#ifndef SCENECAMERA_H
#define SCENECAMERA_H

#include "SceneObject.h"

namespace me::scene {
    // Remember: FOV is vertical
    class SceneCamera : public SceneObject {
        private:
        // Vertical field of view.
        float fieldOfView;

        public:
        inline void SetFOV(float fov);
        [[nodiscard]] inline float GetFOV() const;
    };
}

#endif //SCENECAMERA_H
