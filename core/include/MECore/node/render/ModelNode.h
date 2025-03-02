//
// Created by ryen on 2/26/25.
//

#pragma once

#include <memory.h>

#include "RenderNode.h"
#include "MECore/resource/Model.h"

namespace ME::node {
    class ModelNode : public RenderNode {
        public:
        // Might change this to a shared pointer later
        resource::Model* model;
    };
}
