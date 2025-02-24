//
// Created by ryen on 2/20/25.
//

#include "MECore/node/game/GameNode.h"

#include <algorithm>

namespace ME::node {
    GameNode::GameNode() : transform(this) {
        isRoot = false;
        parent = nullptr;
    }

    GameNode::GameNode(Node* parent) : transform(this) {
        isRoot = true;
        this->parent = parent;
    }

    std::vector<Node*> GameNode::GetChildren() const {
        return std::vector<Node*>(children.begin(), children.end());
    }

    std::vector<GameNode*> GameNode::GetGameChildren() const {
        return children;
    }

    std::vector<GameNode*> GameNode::GetGameDescendants() const {
        std::vector<GameNode*> descendants;
        GetDescendantsInternal(descendants);
        return descendants;
    }

    void GameNode::SetParent(GameNode* parent) {
        // Remove child if applicable
        if (this->parent != nullptr) {
            if (auto cast = dynamic_cast<GameNode*>(this->parent); cast != nullptr) {
                cast->children.erase(std::ranges::find(cast->children, this));
            }
        }

        this->parent = parent;

        // Add child if applicable
        if (parent != nullptr) {
            parent->children.push_back(this);
        }
    }

    void GameNode::GetDescendantsInternal(std::vector<GameNode*>& descendants) const {
        descendants.insert(descendants.end(), children.begin(), children.end());
        for (auto child : children) {
            child->GetDescendantsInternal(descendants);
        }
    }
}
