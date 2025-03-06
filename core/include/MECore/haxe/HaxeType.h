//
// Created by ryen on 12/24/24.
//

#pragma once

#include <string>
#include <vector>

#include "HaxeObject.h"

namespace ME::haxe {
    class HaxeModule;

    // Represents a Haxe Object Type
    class HaxeType {
        private:
        HaxeModule* system;
        hl_module* module;
        hl_type* type;

        std::vector<std::unique_ptr<HaxeObject>> instances;

        public:
        HaxeType(HaxeModule* system, hl_module* module, hl_type* type);

        inline HaxeModule* GetSystem() const { return system; }
        inline hl_type* GetType() const { return type; }

        inline void SetPtr(const FieldName& name, HaxeObject* value) const { hl_dyn_setp(*reinterpret_cast<vdynamic**>(type->obj->global_value), hl_hash_utf8(name.c_str()), type, value->GetDynamic()); }

        HaxeObject* CreateInstance(const bool preserve = true);
        vdynamic* CallStaticMethod(const FuncName& name, FuncArgs& args) const;
    };
}
