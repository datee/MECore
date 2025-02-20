//
// Created by ryen on 2/19/25.
//

#ifndef RENDERROOTNODE_H
#define RENDERROOTNODE_H
#include <vector>

#include "Node.h"
#include "RenderNode.h"

namespace me::node {
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

#endif //RENDERROOTNODE_H
