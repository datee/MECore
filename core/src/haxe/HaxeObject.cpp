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

    vdynamic* HaxeObject::CallMethod(const std::u16string& name, const std::vector<vdynamic*>& args) const {
        hl_obj_proto* target = nullptr;
        for (int i = 0; i < vmType->obj->nproto; i++) {
            auto proto = &vmType->obj->proto[i];
            std::u16string protoName = proto->name;
            if (protoName == name) {
                target = proto;
                break;
            }
        }

        if (target == nullptr) {
            spdlog::error("HaxeObject::CallMethod: unknown static method");
            return nullptr;
        }

        vdynamic* closureArgs[args.size() + 1];
        closureArgs[0] = object;
        for (int i = 0; i < args.size(); ++i) {
            closureArgs[i + 1] = args[i];
        }

        vclosure closure;
        closure.t = module->code->functions[module->functions_indexes[target->findex]].type;
        closure.fun = module->functions_ptrs[target->findex];
        closure.hasValue = false;

        bool except = false;
        auto result = hl_dyn_call_safe(&closure, closureArgs, args.size() + 1, &except);
        if (except) {
            spdlog::error("HaxeObject::CallMethod: exception thrown");
        }
        return result;
    }

}
