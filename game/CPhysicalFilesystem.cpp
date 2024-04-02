#include "CPhysicalFilesystem.h"

CPhysicalFilesystem::CPhysicalFilesystem(const fs::path &rootPath, bool readOnly)
    : m_rootPath(rootPath), m_readOnly(readOnly)
{
}

bool CPhysicalFilesystem::Exists(const fs::path &path) const
{
    return fs::exists(GetFullPath(path));
}

u64 CPhysicalFilesystem::GetSize(const fs::path &path) const
{
    return fs::file_size(GetFullPath(path));
}

std::vector<byte> CPhysicalFilesystem::Read(const fs::path &path, u64 amount, u64 offset) const
{
    fs::path fullPath = GetFullPath(path);
    u64 size = GetSize(fullPath);

    if (amount != 0 && amount < size)
    {
        size = amount;
    }

    std::vector<byte> data(size);

    if (size > 0)
    {
        std::ifstream stream(fullPath, std::ios::in | std::ios::binary);
        if (!stream.is_open())
        {
            return std::vector<byte>();
        }

        stream.read((char *)data.data(), size);
        stream.close();
    }

    return data;
}

u64 CPhysicalFilesystem::Write(const fs::path &path, const std::vector<byte> &data, u64 amount)
{
    if (m_readOnly)
    {
        return 0;
    }

    fs::path fullPath = GetFullPath(path);

    std::ofstream stream(fullPath);
    if (!stream.is_open())
    {
        return 0;
    }

    if (amount == 0 || amount > data.size())
    {
        amount = data.size();
    }

    stream.write((const char *)data.data(), amount);

    return stream.tellp();
}

bool CPhysicalFilesystem::CreateDirectory(const fs::path &path)
{
    if (m_readOnly)
    {
        return false;
    }

    return fs::create_directories(GetFullPath(path));
}

bool CPhysicalFilesystem::Remove(const fs::path &path)
{
    if (m_readOnly)
    {
        return false;
    }

    return fs::remove(GetFullPath(path));
}

void CPhysicalFilesystem::Rename(const fs::path &oldPath, const fs::path &newPath)
{
    if (m_readOnly)
    {
        return;
    }

    fs::rename(GetFullPath(oldPath), GetFullPath(newPath));
}

fs::path CPhysicalFilesystem::GetFullPath(const fs::path &path) const
{
    std::string stringPath = path.generic_string();
    if (stringPath.starts_with(m_rootPath.generic_string()))
    {
        return path;
    }
    else
    {
        return m_rootPath / stringPath.substr(path.root_directory().generic_string().length());
    }
}
