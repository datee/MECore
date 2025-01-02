//
// Created by ryen on 1/2/25.
//

#include "HaxeEngineObject.h"

#include "HaxeType.h"
#include "HaxeGlobals.h"

namespace me::haxe {
    HaxeEngineObject::HaxeEngineObject(HaxeType* type) {
        object = type->CreateInstance();

        // initialize object
        vdynamic ptr;
        ptr.t = &hlt_i64;
        ptr.v.i64 = reinterpret_cast<int64>(this);
        object->CallVirtualMethod(u"ME_Initialize", { &ptr });
    }

    HaxeEngineObject::HaxeEngineObject(const TypeName& typeName) : HaxeEngineObject(mainSystem->GetType(typeName)) {

    }

    HaxeEngineObject::~HaxeEngineObject() {
        object->CallVirtualMethod(u"ME_Destroy", {});
    }


}
