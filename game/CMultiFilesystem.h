#pragma once

#include "shared.h"

#include "IFilesystem.h"

class CMultiFilesystem : public IFilesystem
{
  public:
    CMultiFilesystem() = default;
    ~CMultiFilesystem() = default;

    void AddFilesystem(std::shared_ptr<IFilesystem> filesystem);

    bool Exists(const fs::path &path) const;
    u64 GetSize(const fs::path &path) const;
    std::vector<byte> Read(const fs::path &path, u64 amount, u64 offset) const;
    u64 Write(const fs::path &path, const std::vector<byte> &data, u64 amount);
    bool CreateDirectory(const fs::path &path);
    bool Remove(const fs::path &path);
    void Rename(const fs::path &oldPath, const fs::path &newPath);
    fs::path GetFullPath(const fs::path &path) const;
    fs::path GetRoot() const
    {
        return fs::path();
    }

  private:
    std::vector<std::shared_ptr<IFilesystem>> m_filesystems;

    std::shared_ptr<IFilesystem> GetFirstWithFile(const fs::path &path);
    const std::shared_ptr<IFilesystem> GetFirstWithFileConst(const fs::path &path) const;
};
