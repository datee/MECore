//
// Created by ryen on 12/22/24.
//

#include "HaxeSystem.h"

#include <map>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/ranges.h>

#include "HaxeUtils.cpp"

namespace me::haxe {
    bool HaxeSystem::LoadFromMemory(const std::vector<uint8_t>& data) {
        return LoadFromMemory(data.data(), data.size());
    }

    bool HaxeSystem::LoadFromMemory(const uint8_t* data, int size) {
        char* msg;
        code = hl_code_read(data, size, &msg);

        if (!code) {
            spdlog::error("HaxeSystem::LoadFromMemory: failed to read code");
            return false;
        }

        module = hl_module_alloc(code);
        hl_code_free(code);

        if (!hl_module_init(module, false, false)) {
            spdlog::error("HaxeSystem::LoadFromMemory: failed to initialize module");
            return false;
        }

        return true;
    }

    void HaxeSystem::Release() {
        if (module) return;

        hl_module_free(module);
        hl_free(&code->alloc);

        module = nullptr;
        initialized = false;
    }

    HaxeType* HaxeSystem::GetType(const TypeName& name) {
        if (types.contains(name)) {
            return types[name].get();
        }

        hl_type* result = nullptr;
        for (int i = 0; i < module->code->ntypes; i++) {
            auto type = &module->code->types[i];
            if (type->kind == hl_type_kind::HOBJ) {
                TypeName typeName = type->obj->name;
                if (typeName == name) {
                    result = type;
                    break;
                }
            }
        }

        if (!result) {
            spdlog::error("HaxeSystem::GetType: Failed to find type.");
            return nullptr;
        }

        HaxeType* type = new HaxeType(this, module, result);
        types.insert({ name, std::unique_ptr<HaxeType>(type) });
        return type;
    }

    std::vector<HaxeType*> HaxeSystem::GetTypesWithName(const TypeName& name) {
        std::vector<HaxeType*> result{};

        for (int i = 0; i < module->code->ntypes; i++) {
            auto type = &module->code->types[i];
            if (type->kind == hl_type_kind::HOBJ) {
                TypeName typeName = type->obj->name;
                if (typeName.contains(name)) {
                    HaxeType* haxeType;
                    if (types.contains(typeName)) {
                        haxeType = types[typeName].get();
                    } else {
                        haxeType = new HaxeType(this, module, type);
                        types.insert({ name, std::unique_ptr<HaxeType>(haxeType) });
                    }
                    result.push_back(haxeType);
                }
            }
        }

        return std::move(result);
    }

    void HaxeSystem::Initialize() {
        int entrypoint = module->code->entrypoint;
        vclosure closure;
        closure.t = code->functions[module->functions_indexes[entrypoint]].type;
        closure.fun = module->functions_ptrs[entrypoint];
        closure.hasValue = 0; // static

        bool except = false;
        auto* result = hl_dyn_call_safe(&closure, NULL, 0, &except);
        if (except) {
            Util_PrintException(result);
        } else {
            initialized = true;
        }
    }

}
