//
// Created by ryen on 12/22/24.
//

#ifndef HAXESYSTEM_H
#define HAXESYSTEM_H
#include <map>
#include <memory>
#include <string>

#include "HaxeType.h"

namespace me::haxe {
    class HaxeSystem {
        private:
        std::string filePath;
        hl_code* code;
        hl_module* module;

        std::map<std::u16string, std::unique_ptr<HaxeType>> types;

        public:
        explicit HaxeSystem(std::string path);

        inline hl_module* GetModule() const { return module; }

        bool Load();
        HaxeType* GetType(const std::u16string name);
        void CallEntryPoint();
    };
}

#endif //HAXESYSTEM_H
