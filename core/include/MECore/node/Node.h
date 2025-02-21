//
// Created by ryen on 2/19/25.
//

#pragma once

#include <string>
#include <vector>

namespace ME::node {
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

        virtual Node* GetParent() const = 0;
        virtual std::vector<Node*> GetChildren() const = 0;
    };
}
