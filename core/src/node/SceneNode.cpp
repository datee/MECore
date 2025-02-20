//
// Created by ryen on 2/19/25.
//

#include "MECore/node/SceneNode.h"

namespace ME::node {
    SceneNode::SceneNode() {
        parent = nullptr;
        game = new GameNode(this);
    }

    SceneNode::~SceneNode() {
        for (auto child : children) {
            delete child;
        }
        if (parent != nullptr) {
            parent->children.erase(std::ranges::find(parent->children, this));
        }
        delete game;
    }

    Node* SceneNode::GetParent() const {
        return parent;
    }

    std::vector<Node*> SceneNode::GetChildren() const {
        auto vec = std::vector<Node*>();
        vec.reserve(children.size() + 2);
        vec.insert(vec.end(), { game });
        vec.insert(vec.end(), children.begin(), children.end());
        return vec;
    }

    void SceneNode::SetParent(SceneNode* parent) {
        if (this->parent != nullptr) {
            this->parent->children.erase(std::ranges::find(this->parent->children, this));
        }

        this->parent = parent;

        if (parent != nullptr) {
            parent->children.push_back(this);
        }
    }

}
