//
// Created by ryen on 12/22/24.
//

#include "HaxeSystem.h"

#include <map>

#include "../FileSystem.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/bundled/ranges.h"

namespace me::haxe {
    HaxeSystem::HaxeSystem(const std::string path) {
        filePath = path;
        code = nullptr;
        module = nullptr;
    }

    bool HaxeSystem::Load() {
        auto file = fs::OpenFile(filePath, fs::FileMode::Read);
        bool result = false;
        if (file && file->IsOpened()) {
            size_t size = file->Size();
            unsigned char buffer[size];
            memset(buffer, 0, size);

            file->Read(buffer, size);

            char* msg;
            code = hl_code_read(buffer, size, &msg);

            if (code) {
                module = hl_module_alloc(code);
                if (hl_module_init(module, false, false)) {
                    result = true;
                } else {
                    spdlog::error("Haxe Module Init Error");
                }
            } else {
                spdlog::error("Haxe Code Load Error: %s", msg);
            }

            file->Close();
        }
        return result;
    }

    HaxeType* HaxeSystem::GetType(const std::u16string name) {
        if (types.contains(name)) {
            return types[name].get();
        }

        hl_type* result = nullptr;
        for (int i = 0; i < module->code->ntypes; i++) {
            auto type = &module->code->types[i];
            if (type->kind == hl_type_kind::HOBJ) {
                std::u16string typeName = type->obj->name;
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

    void HaxeSystem::CallEntryPoint() {
        int entrypoint = module->code->entrypoint;
        vclosure closure;
        closure.t = code->functions[module->functions_indexes[entrypoint]].type;
        closure.fun = module->functions_ptrs[entrypoint];
        closure.hasValue = 0; // static

        bool except = false;
        hl_dyn_call_safe(&closure, NULL, 0, &except);
        if (except) {
            spdlog::error("Haxe Entrypoint exception");
        }
        spdlog::info("Haxe Entrypoint finished");
    }

}
