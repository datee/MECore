//
// Created by ryen on 2/19/25.
//

#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>

namespace me::node {
    enum NodeInfo {
        None = 0,

        Root = 1,
        Leaf = Root << 1,

        EditorOnly = Leaf << 1,

        Scene = EditorOnly << 1,
        Game = Scene << 1,
        Physics = Game << 1,
        Render = Physics << 1,
    };

    class Node {
        protected:
        std::string name;

        public:
        virtual ~Node() = default;

        inline std::string GetName() const { return name; }
        inline void SetName(const std::string& name) { this->name = name; }

        virtual Node* GetParent() const;
        virtual std::vector<Node*> GetChildren() const;
    };
}

#endif //NODE_H
