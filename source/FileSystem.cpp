//
// Created by ryen on 12/5/24.
//

#include "FileSystem.h"

namespace me::fs {
    void Initialize() {
        nativeFs = std::make_unique<vfspp::NativeFileSystem>("../data");
        nativeFs->Initialize();

        vfs->AddFileSystem("/", std::move(nativeFs));
    }

    vfspp::IFilePtr OpenFile(const std::string& path, vfspp::IFile::FileMode mode) {
        return vfs->OpenFile(vfspp::FileInfo(path), mode);
    }

    vfspp::IFilePtr OpenFile(const vfspp::FileInfo& info, vfspp::IFile::FileMode mode) {
        return vfs->OpenFile(info, mode);
    }
}
