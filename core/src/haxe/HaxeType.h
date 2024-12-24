//
// Created by ryen on 12/24/24.
//

#ifndef HAXETYPE_H
#define HAXETYPE_H

#include <string>
#include <vector>

#include "HaxeObject.h"

namespace me::haxe {
    class HaxeSystem;

    // Represents a Haxe Object Type
    class HaxeType {
        private:
        HaxeSystem* system;
        hl_module* module;
        hl_type* type;

        std::vector<std::unique_ptr<HaxeObject>> instances;

        public:
        HaxeType(HaxeSystem* system, hl_module* module, hl_type* type);

        inline HaxeSystem* GetSystem() const { return system; }
        inline hl_type* GetType() const { return type; }

        HaxeObject* CreateInstance();
        vdynamic* CallStaticMethod(const std::u16string& name, const std::vector<vdynamic*>& args) const;
    };
}

#endif //HAXETYPE_H
