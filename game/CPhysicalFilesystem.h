#pragma once

#include "shared.h"

#include "IFilesystem.h"

class CPhysicalFilesystem : public IFilesystem
{
  public:
    CPhysicalFilesystem(const fs::path &rootPath = fs::path(""), bool readOnly = true);
    ~CPhysicalFilesystem() = default;

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
        return m_rootPath;
    }

  private:
    fs::path m_rootPath;
    bool m_readOnly;
};
