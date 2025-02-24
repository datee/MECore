//
// Created by ryen on 2/19/25.
//

#pragma once

#include <vector>

#include "../Node.h"
#include "RenderNode.h"

namespace ME::node {
    class RenderRootNode final : public Node {
        friend RenderNode;
        protected:
        Node* parent;
        std::vector<RenderNode*> children;

        public:
        explicit RenderRootNode(Node* parent) {
            this->parent = parent;
            this->name = "RenderRoot";
        }

        Node* GetParent() const override { return parent; }
        std::vector<Node*> GetChildren() const override;
        int GetChildCount() const override { return children.size(); }
        std::vector<RenderNode*> GetRenderChildren() const { return children; }
    };
}
