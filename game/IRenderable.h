#pragma once

#include "shared.h"

class CRenderer;

class IRenderable
{
  public:
    virtual void Draw(const ivec2 &position, float zRotation = 0.0f, const vec2 &scale = vec2(1.0f)) = 0;

  protected:
    std::shared_ptr<CRenderer> m_renderer;
};
