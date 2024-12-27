//
// Created by ryen on 12/24/24.
//

#include "HaxeObject.h"

#include "spdlog/spdlog.h"

namespace me::haxe {
    HaxeObject::HaxeObject(HaxeType* type, hl_type* vmType, hl_module* module, vdynamic* obj) {
        this->type = type;
        this->vmType = vmType;
        this->module = module;
        object = obj;
        hl_add_root(obj);
    }

    HaxeObject::~HaxeObject() {
        hl_remove_root(object);
    }

    inline hl_obj_proto* FindMethod(const hl_type *type, const std::u16string& name) {
        hl_obj_proto* target = nullptr;
        for (int i = 0; i < type->obj->nproto; i++) {
            auto proto = &type->obj->proto[i];
            std::u16string protoName = proto->name;
            if (protoName == name) {
                target = proto;
                break;
            }
        }
        return target;
    }

    inline vdynamic* CallMethodInl(const hl_module* module, const hl_obj_proto* func, vdynamic* instance, const std::vector<vdynamic*>& args, bool* isExcept) {
        vdynamic* closureArgs[args.size() + 1];
        closureArgs[0] = instance;
        for (int i = 0; i < args.size(); ++i) {
            closureArgs[i + 1] = args[i];
        }

        vclosure closure;
        closure.t = module->code->functions[module->functions_indexes[func->findex]].type;
        closure.fun = module->functions_ptrs[func->findex];
        closure.hasValue = false;

        return hl_dyn_call_safe(&closure, closureArgs, args.size() + 1, isExcept);
    }

    vdynamic* HaxeObject::CallMethod(const std::u16string& name, const std::vector<vdynamic*>& args) const {
        hl_obj_proto* target = FindMethod(vmType, name);

        if (target == nullptr) {
            spdlog::error("HaxeObject::CallMethod: unknown method");
            return nullptr;
        }

        bool isExcept = false;
        auto result = CallMethodInl(module, target, object, args, &isExcept);
        if (isExcept) {
            spdlog::error("HaxeObject::CallMethod: exception thrown");
            // TODO: print exception and stack trace
        }
        return result;
    }

    vdynamic* HaxeObject::CallVirtualMethod(const std::u16string& name, const std::vector<vdynamic*>& args) const {
        hl_type* currentType = vmType;
        hl_obj_proto* target = nullptr;
        do {
            target = FindMethod(currentType, name);
            currentType = currentType->obj->super;
        } while (target == nullptr && currentType != nullptr);

        if (target == nullptr) {
            spdlog::error("HaxeObject::CallVirtualMethod: unknown method");
            return nullptr;
        }

        bool isExcept = false;
        auto result = CallMethodInl(module, target, object, args, &isExcept);
        if (isExcept) {
            spdlog::error("HaxeObject::CallVirtualMethod: exception thrown");
            // TODO: print exception and stack trace
        }
        return result;
    }
}
