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
        std::shared_ptr<resource::Model> model;
    };
}
