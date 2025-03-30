//
// Created by ryen on 3/30/25.
//

#include "MECore/node/render/DirectionalLightNode.h"

namespace ME::node {
    Matrix4x4 DirectionalLightNode::GetProjectionMatrix(float zNear, float zFar) const {
        constexpr float width = 5;
        constexpr float height = 5;

        constexpr float top = height * 0.5;
        constexpr float bottom = -height * 0.5;
        constexpr float left = -width * 0.5;
        constexpr float right = width * 0.5;

        float range = 1.0f / (zFar - zNear);

        return Matrix4x4(
            Vector4(2.f / width, 0, 0, 0),
            Vector4(0, 2.f / height, 0, 0),
            Vector4(0, 0, range, 0),
            Vector4(0, 0, -range * zNear, 1));
    }
}
