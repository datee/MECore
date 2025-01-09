//
// Created by ryen on 12/24/24.
//

#include "HaxeObject.h"

#include "spdlog/spdlog.h"
#include "HaxeUtils.cpp"

namespace me::haxe {
    HaxeObject::HaxeObject(HaxeType* type, hl_type* vmType, hl_module* module, vdynamic* obj) {
        this->type = type;
        this->vmType = vmType;
        this->module = module;
        object = obj;
    }

    HaxeObject::~HaxeObject() {
        StopPreserving();
    }

    vdynamic* HaxeObject::CallMethod(const FuncName& name, FuncArgs args) const {
        hl_obj_proto* target = Util_FindMethod(vmType, name);
        if (target == nullptr) {
            spdlog::error("HaxeObject::CallMethod: unknown method");
            return nullptr;
        }

        Util_PrepareInstCall(object, args);

        bool isExcept = false;
        auto result = Util_CallMethod(module, target, args, &isExcept);
        if (isExcept) {
            Util_PrintException(result);
        }
        return result;
    }

    vdynamic* HaxeObject::CallVirtualMethod(const FuncName& name, FuncArgs args) const {
        hl_type* currentType = vmType;
        hl_obj_proto* target = nullptr;
        do {
            target = Util_FindMethod(currentType, name);
            currentType = currentType->obj->super;
        } while (target == nullptr && currentType != nullptr);

        if (target == nullptr) {
            spdlog::error("HaxeObject::CallVirtualMethod: unknown method");
            return nullptr;
        }

        Util_PrepareInstCall(object, args);

        bool isExcept = false;
        auto result = Util_CallMethod(module, target, args, &isExcept);
        if (isExcept) {
            Util_PrintException(result);
        }
        return result;
    }

    void HaxeObject::Preserve() const {
        hl_add_root(object);
    }

    void HaxeObject::StopPreserving() const {
        hl_remove_root(object);
    }
}
