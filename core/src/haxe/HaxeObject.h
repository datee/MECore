//
// Created by ryen on 12/24/24.
//

#ifndef HAXEOBJECT_H
#define HAXEOBJECT_H
#include <hl.h>
#include <memory>
#include <string>
#include <vector>

extern "C" {
#include "hlmodule.h"
}

namespace me::haxe {
    class HaxeType;

    class HaxeObject {
        private:
        HaxeType* type;
        hl_type* vmType;
        hl_module* module;
        vdynamic* object;

        public:
        HaxeObject(HaxeType* type, hl_type* vmType, hl_module* module, vdynamic* obj);
        ~HaxeObject();

        vdynamic* CallMethod(const std::u16string& name, const std::vector<vdynamic*>& args) const;
    };

    typedef std::shared_ptr<HaxeObject> HaxeObjectPtr;
}

#endif //HAXEOBJECT_H
