//
// Created by ryen on 12/24/24.
//

#include "HaxeType.h"

#include "spdlog/spdlog.h"
#include "HaxeUtils.cpp"

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

    vdynamic* HaxeType::CallStaticMethod(const std::u16string& name, std::vector<vdynamic*>& args) const {
        hl_obj_proto* target = Util_FindMethod(type, name);
        if (target == nullptr) {
            spdlog::error("HaxeType::CallStaticMethod: unknown static method");
            return nullptr;
        }

        bool isExcept = false;
        auto result = Util_CallMethod(module, target, args, &isExcept);
        if (isExcept) {
            Util_PrintException(result);
        }
        return result;
    }
}
