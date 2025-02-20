//
// Created by ryen on 2/19/25.
//

#pragma once

#include "../Node.h"

namespace ME::node {
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
