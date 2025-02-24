//
// Created by ryen on 2/24/25.
//

#include "MECore/node/render/RenderRootNode.h"
#include "MECore/node/render/RenderNode.h"

namespace ME::node {
    std::vector<Node*> RenderRootNode::GetChildren() const {
        return std::vector<Node*>(children.begin(), children.end());
    }

}
