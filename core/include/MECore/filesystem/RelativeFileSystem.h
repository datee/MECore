//
// Created by ryen on 3/6/25.
//

#pragma once

#include "IFileSystem.h"

namespace ME::filesystem {
    class RelativeFileSystem : public IFileSystem {
        private:
        std::shared_ptr<IFileSystem> realFs;
        std::filesystem::path basePath;

    public:
        RelativeFileSystem(std::shared_ptr<IFileSystem> fs, const std::filesystem::path& basePath);

        const std::filesystem::path& GetBasePath() const { return basePath; }

        bool FileExists(const std::filesystem::path& path) override;
        bool FolderExists(const std::filesystem::path& path) override;

        std::shared_ptr<IFile> ReadFile(const std::filesystem::path& path) override;
        bool WriteFile(const std::filesystem::path& path, const void* data, size_t size) override;

        int EnumerateFiles(const std::filesystem::path& path, const std::vector<std::string>& extensions, EnumerateCallback callback, bool allowDuplicates) override;
        int EnumerateFolders(const std::filesystem::path& path, EnumerateCallback callback, bool allowDuplicates) override;

        std::filesystem::path GetRealPath(const std::filesystem::path& path) override;
    };
}
