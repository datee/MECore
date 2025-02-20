//
// Created by ryen on 2/19/25.
//

#ifndef RENDERNODE_H
#define RENDERNODE_H
#include "Node.h"

namespace me::node {
    class RenderRootNode;

    class RenderNode : public Node {
        protected:
        RenderRootNode* root;
        // TODO: add transform and enabled flag

        public:
        RenderNode();
        ~RenderNode() override;

        Node* GetParent() const override;

        void SetRoot(RenderRootNode* root);
    };
}

#endif //RENDERNODE_H
