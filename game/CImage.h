#pragma once

#include "shared.h"

#include "IFilesystem.h"
#include "IRenderable.h"

class CRenderer;

class CImage : IRenderable
{
  public:
    CImage(CRenderer &renderer, const std::shared_ptr<IFilesystem> filesystem, const fs::path &path);
    ~CImage();

    void Draw(CRenderer &renderer, const ivec2 &position, float zRotation, const vec2 &scale);

  private:
    SDL_Texture *m_texture;
    ivec2 m_size;
};
