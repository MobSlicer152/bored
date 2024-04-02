#include "CMultiFilesystem.h"

void CMultiFilesystem::AddFilesystem(std::shared_ptr<IFilesystem> filesystem)
{
    m_filesystems.push_back(filesystem);
}

bool CMultiFilesystem::Exists(const fs::path &path) const
{
    return GetFirstWithFileConst(path)->Exists(path);
}

u64 CMultiFilesystem::GetSize(const fs::path &path) const
{
    const std::shared_ptr<IFilesystem> filesystem = GetFirstWithFileConst(path);
    if (filesystem)
    {
        return filesystem->GetSize(path);
    }

    return 0;
}

std::vector<byte> CMultiFilesystem::Read(const fs::path &path, u64 amount, u64 offset) const
{
    const std::shared_ptr<IFilesystem> filesystem = GetFirstWithFileConst(path);
    if (filesystem)
    {
        return filesystem->Read(path, amount, offset);
    }

    return std::vector<byte>();
}

u64 CMultiFilesystem::Write(const fs::path &path, const std::vector<byte> &data, u64 amount)
{
    std::shared_ptr<IFilesystem> filesystem = GetFirstWithFile(path);
    if (filesystem)
    {
        return filesystem->Write(path, data, amount);
    }

    return 0;
}

bool CMultiFilesystem::CreateDirectory(const fs::path &path)
{
    std::shared_ptr<IFilesystem> filesystem = GetFirstWithFile(path);
    if (filesystem)
    {
        return filesystem->CreateDirectory(path);
    }

    return false;
}

bool CMultiFilesystem::Remove(const fs::path &path)
{
    std::shared_ptr<IFilesystem> filesystem = GetFirstWithFile(path);
    if (filesystem)
    {
        return filesystem->Remove(path);
    }

    return false;
}

void CMultiFilesystem::Rename(const fs::path &oldPath, const fs::path &newPath)
{
    std::shared_ptr<IFilesystem> filesystem = GetFirstWithFile(oldPath);
    if (filesystem)
    {
        return filesystem->Rename(oldPath, newPath);
    }
}

fs::path CMultiFilesystem::GetFullPath(const fs::path &path) const
{
    const std::shared_ptr<IFilesystem> filesystem = GetFirstWithFileConst(path);
    if (filesystem)
    {
        return filesystem->GetFullPath(path);
    }

    return fs::path();
}

std::shared_ptr<IFilesystem> CMultiFilesystem::GetFirstWithFile(const fs::path &path)
{
    for (std::shared_ptr<IFilesystem> filesystem : m_filesystems)
    {
        if (filesystem->Exists(path))
        {
            return filesystem;
        }
    }

    return nullptr;
}

const std::shared_ptr<IFilesystem> CMultiFilesystem::GetFirstWithFileConst(const fs::path &path) const
{
    for (const std::shared_ptr<IFilesystem> filesystem : m_filesystems)
    {
        if (filesystem->Exists(path))
        {
            return filesystem;
        }
    }

    return nullptr;
}
