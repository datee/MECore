//
// Created by ryen on 12/5/24.
//

#include "MECore/fs/FileSystem.h"

namespace ME::filesystem {
    void Initialize() {
        vfs = std::make_shared<vfspp::VirtualFileSystem>();

        // Initially there was a data filesystem by default but i decided that app should set up everything here
        // dataFs = std::make_shared<vfspp::NativeFileSystem>("../data");
        // dataFs->Initialize();
        // vfs->AddFileSystem("/gamedata/", dataFs);

        // Set shortcut
        fs = vfs;
    }

    void Shutdown() {
        vfs = nullptr;
        // dataFs = nullptr;
    }
}
