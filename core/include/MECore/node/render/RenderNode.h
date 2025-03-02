//
// Created by ryen on 2/19/25.
//

#pragma once

#include "MECore/math/Transform.h"
#include "../Node.h"

namespace ME::node {
    class RenderRootNode;
    class RenderNode : public Node {
        protected:
        RenderRootNode* root = nullptr;
        Transform transform{};
        bool enabled = true;

        public:
        RenderNode() = default;
        ~RenderNode() override;

        Node* GetParent() const override;
        std::vector<Node*> GetChildren() const override {
            return std::vector<Node*>();
        }
        int GetChildCount() const override { return 0; }

        Transform& GetTransform() { return transform; }
        bool IsEnabled() const { return enabled; }

        void SetEnabled(bool val) { enabled = val; }
        void SetRoot(RenderRootNode* root);
    };
}
