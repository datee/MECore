//
// Created by ryen on 12/7/24.
//

#include "SceneCamera.h"

#include "../../render/MainWindow.h"

namespace me::scene {
    SceneCamera::SceneCamera() {
        zNear = 0.01f;
        zFar = 1000.0f;
        fieldOfView = 60.0f;

        usingCustomProjection = false;
        RegenerateMatrix();
    }

    void SceneCamera::RegenerateMatrix() {
        projection = math::Matrix4x4::Perspective(fieldOfView * mathfu::kDegreesToRadians, window::aspect, zNear, zFar, -1);
    }
}
