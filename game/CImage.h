#pragma once

#include "shared.h"

#include "IFilesystem.h"
#include "IRenderable.h"

class CRenderer;

class CImage : public IRenderable
{
  public:
    CImage(std::shared_ptr<CRenderer> renderer, const IFilesystem& filesystem, const fs::path &path);
    ~CImage();

    void Draw(const ivec2 &position, float zRotation = 0.0f, const vec2 &scale = vec2(1.0f));

  private:
    SDL_Texture *m_texture;
    ivec2 m_size;
};
