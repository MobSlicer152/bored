#pragma once

#include "shared.h"

#include "IRenderable.h"

class CImage : IRenderable
{
  public:
    CImage(const fs::path &path);
    ~CImage();

    void Draw(const ivec2 &position, float zRotation, const vec2 &scale);

  private:
    SDL_Texture *m_texture;
    ivec2 m_size;
};
