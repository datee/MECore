//
// Created by ryen on 12/7/24.
//

#include "SceneCamera.h"

#include "render/RenderGlobals.h"
#include "render/Window.h"

namespace me::scene {
    SceneCamera::SceneCamera() : SceneObject(u"me.scene.SceneCamera") {
        zNear = 0.01f;
        zFar = 1000.0f;
        fieldOfView = 60.0f;

        usingCustomProjection = false;
        RegenerateMatrix();
    }

    void SceneCamera::RegenerateMatrix() {
        projection = math::Matrix4x4::sPerspective(fieldOfView * math::DEG_TO_RAD, render::mainWindow->GetAspect(), zNear, zFar);
    }
}
