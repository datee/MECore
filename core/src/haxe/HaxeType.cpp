//
// Created by ryen on 12/24/24.
//

#include "HaxeType.h"

#include "spdlog/spdlog.h"

namespace me::haxe {
    HaxeType::HaxeType(HaxeSystem* system, hl_module* module, hl_type* type) {
        this->system = system;
        this->module = module;
        this->type = type;
    }

    HaxeObject* HaxeType::CreateInstance() {
        auto obj = hl_alloc_obj(type);
        auto ptr = new HaxeObject(this, type, module, obj);
        instances.push_back(std::unique_ptr<HaxeObject>(ptr));
        return ptr;
    }

    vdynamic* HaxeType::CallStaticMethod(const std::u16string& name, const std::vector<vdynamic*>& args) const {
        hl_obj_proto* target = nullptr;
        for (int i = 0; i < type->obj->nproto; i++) {
            auto proto = &type->obj->proto[i];
            std::u16string protoName = proto->name;
            if (protoName == name) {
                target = proto;
                break;
            }
        }

        if (target == nullptr) {
            spdlog::error("HaxeType::CallStaticMethod: unknown static method");
            return nullptr;
        }

        vclosure closure;
        closure.t = module->code->functions[module->functions_indexes[target->findex]].type;
        closure.fun = module->functions_ptrs[target->findex];
        closure.hasValue = false;

        bool except = false;
        auto result = hl_dyn_call_safe(&closure, const_cast<vdynamic**>(args.data()), args.size(), &except);
        if (except) {
            spdlog::error("HaxeType::CallStaticMethod: exception thrown");
        }
        return result;
    }
}
