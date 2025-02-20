//
// Created by ryen on 2/19/25.
//

#pragma once

#include <vector>

#include "../Node.h"
#include "RenderNode.h"

namespace ME::node {
    class RenderRootNode final : public Node {
        protected:
        Node* parent;
        std::vector<RenderNode*> children;

        public:
        explicit RenderRootNode(Node* parent);

        Node* GetParent() const override;
        std::vector<Node*> GetChildren() const override;
    };
}
