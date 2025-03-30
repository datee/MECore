//
// Created by ryen on 3/30/25.
//

#pragma once

#include "LightNode.h"

namespace ME::node {
    class DirectionalLightNode final : public LightNode {
        public:
        Matrix4x4 GetProjectionMatrix(float zNear, float zFar) const;
    };
}
