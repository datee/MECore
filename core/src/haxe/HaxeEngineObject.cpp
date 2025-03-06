//
// Created by ryen on 1/2/25.
//

#include "MECore/haxe/HaxeEngineObject.h"
#include "MECore/haxe/HaxeType.h"
#include "MECore/haxe/HaxeSystem.h"

namespace ME::haxe {
    HaxeEngineObject::HaxeEngineObject(HaxeType* type, const bool preserve) {
        object = type->CreateInstance(preserve);

        // initialize object
        vdynamic ptr;
        ptr.t = &hlt_i64;
        ptr.v.i64 = reinterpret_cast<int64>(this);
        object->CallVirtualMethod(u"ME_Initialize", { &ptr });
    }

    HaxeEngineObject::HaxeEngineObject(const TypeName& typeName, const bool preserve) : HaxeEngineObject(mainSystem->GetType(typeName), preserve) {

    }

    HaxeEngineObject::~HaxeEngineObject() {
        object->CallVirtualMethod(u"ME_Destroy", {});
    }


}
