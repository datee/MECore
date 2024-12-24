//
// Created by ryen on 12/22/24.
//

#ifndef HAXESYSTEM_H
#define HAXESYSTEM_H
#include <string>
extern "C" {
#include "hlmodule.h"
}

namespace me::haxe {
    class HaxeSystem {
        private:
        std::string filePath;
        hl_code* code;
        hl_module* module;

        public:
        explicit HaxeSystem(std::string path);

        bool Load();

        void CallEntryPoint();
    };
}

#endif //HAXESYSTEM_H
