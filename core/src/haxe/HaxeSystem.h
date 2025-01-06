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

        std::map<TypeName, std::unique_ptr<HaxeType>> types;

        public:
        explicit HaxeSystem(const std::string& path);

        inline hl_module* GetModule() const { return module; }

        bool Load();
        void Release();

        HaxeType* GetType(const TypeName& name);
        std::vector<HaxeType*> GetTypesWithName(const TypeName& name);

        void CallEntryPoint();
    };
}

#endif //HAXESYSTEM_H
