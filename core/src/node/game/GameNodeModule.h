//
// Created by ryen on 2/20/25.
//

#ifndef GAMENODEMODULE_H
#define GAMENODEMODULE_H

namespace me::node {
    class GameNode;

    class GameNodeModule {
        protected:
        GameNode* gameNode;

        explicit GameNodeModule(GameNode* node) { gameNode = node; }
    };
}

#endif //GAMENODEMODULE_H
