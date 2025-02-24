//
// Created by ryen on 2/24/25.
//

#include "MECore/node/render/RenderNode.h"
#include "MECore/node/render/RenderRootNode.h"

namespace ME::node {
    RenderNode::RenderNode() {
        root = nullptr;
    }

    RenderNode::~RenderNode() {
        SetRoot(nullptr);
    }

    Node* RenderNode::GetParent() const {
        return root;
    }

    void RenderNode::SetRoot(RenderRootNode* root) {
        if (this->root != nullptr) {
            this->root->children.erase(std::find(this->root->children.begin(), this->root->children.end(), this));
        }
        this->root = root;
        if (this->root != nullptr) {
            this->root->children.push_back(this);
        }
    }

}
