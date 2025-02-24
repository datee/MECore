//
// Created by ryen on 2/19/25.
//

#pragma once

#include <vector>

#include "GameTransform.h"
#include "../Node.h"

namespace ME::node {
    class GameNode : public Node {
        protected:
        bool isRoot;
        Node* parent;
        std::vector<GameNode*> children;

        GameTransform transform;

        void GetDescendantsInternal(std::vector<GameNode*>& descendants) const;

        public:
        GameNode();
        explicit GameNode(Node* parent); // Use this only if you want to make a root node. Otherwise, use SetParent.

        Node* GetParent() const { return parent; }
        GameNode* GetGameParent() const { return dynamic_cast<GameNode*>(parent); }
        std::vector<Node*> GetChildren() const override;
        int GetChildCount() const override { return children.size(); }

        std::vector<GameNode*> GetGameChildren() const;
        std::vector<GameNode*> GetGameDescendants() const;

        inline GameTransform& GetTransform() { return transform; }

        void SetParent(GameNode* parent);
    };
}
