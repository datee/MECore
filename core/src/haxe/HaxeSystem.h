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
        bool initialized;
        hl_code* code;
        hl_module* module;

        std::map<TypeName, std::unique_ptr<HaxeType>> types;

        public:
        HaxeSystem() = default;

        inline bool IsInitialized() const { return initialized; }
        inline hl_module* GetModule() const { return module; }

        bool LoadFromMemory(const std::vector<uint8_t>& data);
        bool LoadFromMemory(const uint8_t* data, int size);
        void Release();

        void Initialize();

        HaxeType* GetType(const TypeName& name);
        std::vector<HaxeType*> GetTypesWithName(const TypeName& name);
    };
}

#endif //HAXESYSTEM_H
