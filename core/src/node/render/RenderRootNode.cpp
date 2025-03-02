//
// Created by ryen on 2/24/25.
//

#include "MECore/node/render/RenderRootNode.h"

namespace ME::node {
    void RenderRootNode::AddChild(RenderNode* child) {
        if (child == nullptr) return;

        children.push_back(child);
        if (auto model = dynamic_cast<ModelNode*>(child)) {
            models.insert(model);
        }
    }

    void RenderRootNode::RemoveChild(RenderNode* child) {
        if (child == nullptr) return;

        children.erase(std::ranges::find(children, child));
        if (auto model = dynamic_cast<ModelNode*>(child)) {
            models.erase(model);
        }
    }

}
