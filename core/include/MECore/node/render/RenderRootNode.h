//
// Created by ryen on 2/19/25.
//

#pragma once

#include <unordered_set>
#include <vector>

#include "../Node.h"
#include "RenderNode.h"
#include "ModelNode.h"

namespace ME::node {
    class RenderRootNode final : public Node {
        protected:
        Node* parent;
        std::vector<RenderNode*> children;

        std::unordered_set<ModelNode*> models;

        public:
        explicit RenderRootNode(Node* parent) {
            this->parent = parent;
            this->name = "RenderRoot";
        }

        Node* GetParent() const override { return parent; }
        std::vector<Node*> GetChildren() const override { return std::vector<Node*>(children.begin(), children.end()); }
        int GetChildCount() const override { return children.size(); }
        std::vector<RenderNode*> GetRenderChildren() const { return children; }

        std::unordered_set<ModelNode*> GetModels() const { return models; }

        void AddChild(RenderNode* child);
        void RemoveChild(RenderNode* child);
    };
}
