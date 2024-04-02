#pragma once

#include "shared.h"

#include "CImage.h"
#include "IRenderable.h"

class CSpriteSheet : CImage
{
  public:
    CSpriteSheet(const fs::path &path, u32 tileSize = 16) : CImage(path), m_tileSize(tileSize)
    {
    }

    u32 GetTileSize()
    {
        return m_tileSize;
    }

  private:
    u32 m_tileSize;
};
