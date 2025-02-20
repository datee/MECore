//
// Created by ryen on 2/19/25.
//

#ifndef GAMENODE_H
#define GAMENODE_H

#include <vector>

#include "../Node.h"

namespace me::node {
    class GameNode : public Node {
        protected:
        bool isRoot;
        Node* parent;
        std::vector<GameNode*> children;

        public:
        GameNode();
        explicit GameNode(Node* parent); // Use this only if you want to make a root node. Otherwise, use SetParent.

        Node* GetParent() const override;
        std::vector<Node*> GetChildren() const override;

        void SetParent(GameNode* parent);
    };
}

#endif //GAMENODE_H
