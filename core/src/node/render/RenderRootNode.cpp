//
// Created by ryen on 2/24/25.
//

#include "MECore/node/render/RenderRootNode.h"

namespace ME::node {
    // Do not call. Used internally.
    void RenderRootNode::AddChild(RenderNode* child) {
        if (child == nullptr) return;

        children.push_back(child);
        if (auto model = dynamic_cast<ModelNode*>(child)) {
            models.insert(model);
        }
        if (auto light = dynamic_cast<LightNode*>(child)) {
            lights.insert(light);
        }
    }

    // Do not call. Used internally.
    void RenderRootNode::RemoveChild(RenderNode* child) {
        if (child == nullptr) return;

        children.erase(std::ranges::find(children, child));
        if (auto model = dynamic_cast<ModelNode*>(child)) {
            models.erase(model);
        }
        if (auto light = dynamic_cast<LightNode*>(child)) {
            lights.erase(light);
        }
    }

}
