//
// Created by ryen on 1/1/25.
//

#ifndef HAXEENGINEOBJECT_H
#define HAXEENGINEOBJECT_H
#include "HaxeObject.h"

namespace me::haxe {
    class HaxeEngineObject {
        protected:
        HaxeObject* object;

        explicit HaxeEngineObject(HaxeType* type, const bool preserve);
        explicit HaxeEngineObject(const TypeName& typeName, const bool preserve = true);
        virtual ~HaxeEngineObject();

        public:

        [[nodiscard]] HaxeObject* GetHaxeObject() const { return object; }
    };
}

#endif //HAXEENGINEOBJECT_H
