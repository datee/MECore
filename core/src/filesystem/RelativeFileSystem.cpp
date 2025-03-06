//
// Created by ryen on 3/6/25.
//

#include "MECore/filesystem/RelativeFileSystem.h"

namespace ME::filesystem {
    RelativeFileSystem::RelativeFileSystem(std::shared_ptr<IFileSystem> fs, const std::filesystem::path& basePath) {
        realFs = std::move(fs);
        this->basePath = basePath.lexically_normal();
    }

    bool RelativeFileSystem::FileExists(const std::filesystem::path& path) {
        return realFs->FileExists(basePath / path.relative_path());
    }

    bool RelativeFileSystem::FolderExists(const std::filesystem::path& path) {
        return realFs->FolderExists(basePath / path.relative_path());
    }

    std::shared_ptr<IFile> RelativeFileSystem::ReadFile(const std::filesystem::path& path) {
        return realFs->ReadFile(basePath / path.relative_path());
    }

    bool RelativeFileSystem::WriteFile(const std::filesystem::path& path, const void* data, size_t size) {
        return realFs->WriteFile(basePath / path.relative_path(), data, size);
    }

    int RelativeFileSystem::EnumerateFiles(const std::filesystem::path& path, const std::vector<std::string>& extensions, EnumerateCallback callback, bool allowDuplicates) {
        return realFs->EnumerateFiles(basePath / path.relative_path(), extensions, callback, allowDuplicates);
    }

    int RelativeFileSystem::EnumerateFolders(const std::filesystem::path& path, EnumerateCallback callback, bool allowDuplicates) {
        return realFs->EnumerateFolders(basePath / path.relative_path(), callback, allowDuplicates);
    }

    std::filesystem::path RelativeFileSystem::GetRealPath(const std::filesystem::path& path) {
        return realFs->GetRealPath(basePath / path.relative_path());
    }

}
