#pragma once

#include "shared.h"

#include "CSpriteSheet.h"
#include "IRenderable.h"

class CSprite : IRenderable
{
  public:
    CSprite(const CSpriteSheet &sheet, const ivec2 &offset, const ivec2 &size)
        : m_sheet(sheet), m_offset(offset), m_size(size)
    {
    }
    ~CSprite() = default;

    void Draw(CRenderer &renderer, const ivec2 &position, float zRotation, const vec2 &scale);

  private:
    const CSpriteSheet &m_sheet;
    ivec2 m_offset;
    ivec2 m_size;
};
