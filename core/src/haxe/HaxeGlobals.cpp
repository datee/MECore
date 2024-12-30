//
// Created by ryen on 12/29/24.
//

#include "HaxeGlobals.h"

#include "fs/FileSystem.h"

namespace me::haxe {
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
            mainSystem = nullptr;
        }

        hl_unregister_thread();
        delete stackTop;

        hl_global_free();
    }

    bool CreateMainSystem(const std::string& path) {
        // TODO: allow file check before creation
        auto system = new HaxeSystem(path);
        if (!system->Load()) {
            delete system;
            return false;
        }

        mainSystem = std::unique_ptr<HaxeSystem>(system);
        return true;
    }

}
