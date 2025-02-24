//
// Created by ryen on 2/24/25.
//

#include "MECore/node/render/RenderCamera.h"
#include "MECore/render/RenderGlobals.h"

namespace ME::node {
    RenderCamera::RenderCamera() {
        fieldOfView = 60.0f;
        zNear = 0.1f;
        zFar = 1000.0f;
        RegenerateMatrix();
    }

    void RenderCamera::RegenerateMatrix() {
        float height = 1.0f / tanf((fieldOfView * DEG_TO_RAD) * 0.5f);
        float width = height / render::mainWindow->GetAspect();
        float range = zFar / (zFar - zNear);

        projectionMatrix = Matrix4x4(
            Vector4(width, 0.0f, 0.0f, 0.0f),
            Vector4(0.0f, height, 0.0f, 0.0f),
            Vector4(0.0f, 0.0f, range, 1),
            Vector4(0.0f, 0.0f, -zNear * range, 0.0f));
    }
}
