//
// Created by ryen on 2/19/25.
//

#pragma once

#include "Node.h"
#include "game/GameNode.h"
#include "render/RenderRootNode.h"

namespace ME::node {
    // Figure out how to fit scene systems in here

    enum class NodeMode {
        Link, // Forwards everything to parent (Doesn't carry objects when moving)
        Append, // Isolated but treated as one in the api
        Isolate // Completely isolated
    };

    class SceneNode : public Node {
        protected:
        SceneNode* parent;
        GameNode* game;
        RenderRootNode* render;

        std::vector<SceneNode*> children;

        public:
        SceneNode();
        ~SceneNode() override;

        Node* GetParent() const override;
        std::vector<Node*> GetChildren() const override;
        int GetChildCount() const override { return children.size() + 2; }

        GameNode* GetGameNode() const {
            return game;
        }
        RenderRootNode* GetRenderNode() const {
            return render;
        }

        void SetParent(SceneNode* parent);
    };
}
