//
// Created by ryen on 12/5/24.
//

#include "MECore/filesystem/FileSystem.h"

namespace ME::filesystem {
    void Initialize() {
        root = new RootFileSystem();
        fs = root;
    }

    void Shutdown() {
        root = nullptr;
        fs = nullptr;
    }
}
