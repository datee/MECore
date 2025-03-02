//
// Created by ryen on 2/24/25.
//

#include "MECore/node/render/RenderNode.h"
#include "MECore/node/render/RenderRootNode.h"

namespace ME::node {
    RenderNode::~RenderNode() {
        SetRoot(nullptr);
    }

    Node* RenderNode::GetParent() const {
        return root;
    }

    void RenderNode::SetRoot(RenderRootNode* root) {
        if (this->root != nullptr) {
            this->root->RemoveChild(this);
        }
        this->root = root;
        if (this->root != nullptr) {
            this->root->AddChild(this);
        }
    }

}
