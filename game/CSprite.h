#pragma once

#include "shared.h"

#include "CSpriteSheet.h"
#include "IRenderable.h"

class CSprite : IRenderable
{
  public:
    CSprite(const CSpriteSheet &sheet, const ivec2 &offset, const ivec2 &size);
    ~CSprite() = default;

    void Draw(const ivec2 &position, float zRotation, const vec2 &scale);

  private:
    const CSpriteSheet &sheet;
    ivec2 offset;
    ivec2 size;
};
