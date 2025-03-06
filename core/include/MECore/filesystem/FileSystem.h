//
// Created by ryen on 12/5/24.
//

#pragma once

#include "RootFileSystem.h"
#include "NativeFileSystem.h"
#include "RelativeFileSystem.h"

namespace ME {
    // Shortcut to filesystem::vfs
    inline filesystem::RootFileSystem* fs;
}

namespace ME::filesystem {
    inline RootFileSystem* root;

    void Initialize();
    void Shutdown();
}
