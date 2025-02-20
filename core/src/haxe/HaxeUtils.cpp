//
// Created by ryen on 12/26/24.
//

#include <spdlog/spdlog.h>

#include "MECore/haxe/HaxeCommon.h"

namespace ME::haxe {
    inline hl_obj_proto* Util_FindMethod(const hl_type *type, const FuncName& name) {
        hl_obj_proto* target = nullptr;
        for (int i = 0; i < type->obj->nproto; i++) {
            auto proto = &type->obj->proto[i];
            FuncName protoName = proto->name;
            if (protoName == name) {
                target = proto;
                break;
            }
        }
        return target;
    }

    inline void Util_PrepareInstCall(vdynamic* inst, FuncArgs& args) {
        args.insert(args.begin(), inst);
    }

    inline vdynamic* Util_CallMethod(const hl_module* module, const hl_obj_proto* func, FuncArgs& args, bool* isExcept) {
        vclosure closure;
        closure.t = module->code->functions[module->functions_indexes[func->findex]].type;
        closure.fun = module->functions_ptrs[func->findex];
        closure.hasValue = false;

        return hl_dyn_call_safe(&closure, args.data(), args.size(), isExcept);
    }

    inline void Util_PrintException(vdynamic* result) {
        std::string str = fmt::format("Uncaught exception: {}\n", hl_to_utf8(hl_to_string(result)));
        varray* stack = hl_exception_stack();
        for (int i = 0; i < stack->size; i++) {
            str += fmt::format("\n{}", hl_to_utf8(hl_aptr(stack, uchar*)[i]));
        }
        spdlog::error(str);
    }
}
