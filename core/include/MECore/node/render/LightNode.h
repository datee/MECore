//
// Created by ryen on 3/30/25.
//

#pragma once

#include "RenderNode.h"

namespace ME::node {
    class LightNode : public RenderNode {
        public:
        Vector4 color;
        float intensity;
    };
}
