//
// Created by ryen on 12/5/24.
//

#pragma once

#include <vfspp/VFS.h>

namespace ME {
    // Shortcut to filesystem::vfs
    inline vfspp::VirtualFileSystemPtr fs;
}

namespace ME::filesystem {
    inline vfspp::VirtualFileSystemPtr vfs;

    void Initialize();
    void Shutdown();
}
