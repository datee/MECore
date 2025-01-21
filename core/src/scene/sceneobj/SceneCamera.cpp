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
        float height = 1.0f / tanf((fieldOfView * math::DEG_TO_RAD) * 0.5f);
        float width = height / render::mainWindow->GetAspect();
        float range = zFar / (zFar - zNear);

        projection = math::Matrix4x4(
            math::Vector4(width, 0.0f, 0.0f, 0.0f),
            math::Vector4(0.0f, height, 0.0f, 0.0f),
            math::Vector4(0.0f, 0.0f, range, 1),
            math::Vector4(0.0f, 0.0f, -zNear * range, 0.0f));
    }
}
