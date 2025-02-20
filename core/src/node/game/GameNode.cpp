//
// Created by ryen on 2/20/25.
//

#include "../../../include/MECore/node/game/GameNode.h"

#include <algorithm>

namespace ME::node {
    GameNode::GameNode() {
        isRoot = false;
        parent = nullptr;
    }

    GameNode::GameNode(Node* parent) {
        isRoot = true;
        this->parent = parent;
    }

    Node* GameNode::GetParent() const {
        return parent;
    }

    std::vector<Node*> GameNode::GetChildren() const {
        return std::vector<Node*>(children.begin(), children.end());
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

}
