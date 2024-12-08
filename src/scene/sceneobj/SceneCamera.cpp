//
// Created by ryen on 12/7/24.
//

#include "SceneCamera.h"

#include "../../render/MainWindow.h"

namespace me::scene {
    SceneCamera::SceneCamera() {
        fieldOfView = 60.0f;
        usingCustomProjection = false;
        RegenerateMatrix();
    }

    void SceneCamera::RegenerateMatrix() {
        kmMat4PerspectiveProjection(&projection, fieldOfView, window::aspect, zNear, zFar);
    }
}
