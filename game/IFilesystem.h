#pragma once

#include "shared.h"

class IFilesystem
{
  public:
    virtual bool Exists(const fs::path &path) const = 0;
    virtual u64 GetSize(const fs::path &path) const = 0;
    virtual std::vector<byte> Read(const fs::path &path, u64 amount = 0, u64 offset = 0) const = 0;
    virtual u64 Write(const fs::path &path, const std::vector<byte> &data, u64 amount = 0) = 0;
    virtual bool CreateDirectory(const fs::path &path) = 0;
    virtual bool Remove(const fs::path &path) = 0;
    virtual void Rename(const fs::path &oldPath, const fs::path &newPath) = 0;
    virtual fs::path GetFullPath(const fs::path &path) const = 0;
    virtual fs::path GetRoot() const = 0;
};
