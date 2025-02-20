//
// Created by ryen on 2/20/25.
//

#pragma once

namespace ME::node {
    class GameNode;

    class GameNodeModule {
        protected:
        GameNode* gameNode;

        explicit GameNodeModule(GameNode* node) { gameNode = node; }
    };
}
