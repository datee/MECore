//
// Created by ryen on 12/22/24.
//

#pragma once

#include <map>
#include <memory>
#include <string>

#include "HaxeType.h"

namespace ME::haxe {
    class HaxeModule {
        private:
        bool initialized;
        hl_code* code;
        hl_module* module;

        std::map<TypeName, std::unique_ptr<HaxeType>> types;

        public:
        HaxeModule() = default;

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
