#pragma once

#include "shared.h"

#include "CImage.h"
#include "IRenderable.h"

class CSpriteSheet : public CImage
{
  public:
    CSpriteSheet(std::shared_ptr<CRenderer> renderer, const IFilesystem &filesystem,
                 const fs::path &path,
                 u32 tileSize = 16)
        : CImage(renderer, filesystem, path), m_tileSize(tileSize)
    {
    }

    u32 GetTileSize()
    {
        return m_tileSize;
    }

  private:
    u32 m_tileSize;
};
