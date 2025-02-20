//
// Created by ryen on 12/29/24.
//

#include "MECore/haxe/HaxeCommon.h"
#include "MECore/haxe/HaxeGlobals.h"

namespace ME::haxe {
    const char* file = "/assets/code.hl";

    struct HaxeThreadStack {
        int padding;
    };

    static HaxeThreadStack* stackTop;

    void Initialize(int argc, void** argv) {
        hl_global_init();
        hl_sys_init(argv, argc, const_cast<char*>(file));

        stackTop = new HaxeThreadStack();
        hl_register_thread(stackTop);
    }

    void Shutdown() {
        if (mainSystem) {
            mainSystem->Release();
            mainSystem = nullptr;
        }

        hl_unregister_thread();
        delete stackTop;

        hl_global_free();
    }
}
