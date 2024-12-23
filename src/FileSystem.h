//
// Created by ryen on 12/5/24.
//

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "vfspp/VFS.h"

namespace me::fs {
    typedef vfspp::IFile::FileMode FileMode;
    typedef vfspp::IFilePtr FilePtr;

    static vfspp::VirtualFileSystemPtr vfs;
    static vfspp::IFileSystemPtr nativeFs;

    void Initialize();
    FilePtr OpenFile(const std::string& path, FileMode mode = FileMode::Read);
    FilePtr OpenFile(const vfspp::FileInfo& info, FileMode mode = FileMode::Read);
}

#endif //FILESYSTEM_H
