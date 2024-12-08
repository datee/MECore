//
// Created by ryen on 12/5/24.
//

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "vfspp/VFS.h"

namespace me::fs {
    static vfspp::VirtualFileSystemPtr vfs;
    static vfspp::IFileSystemPtr nativeFs;

    void Initialize();
    vfspp::IFilePtr OpenFile(const std::string& path, vfspp::IFile::FileMode mode = vfspp::IFile::FileMode::Read);
    vfspp::IFilePtr OpenFile(const vfspp::FileInfo& info, vfspp::IFile::FileMode mode = vfspp::IFile::FileMode::Read);
}

#endif //FILESYSTEM_H
