#pragma once

#include "shared.h"

class CRenderer;

class IRenderable
{
  public:
    virtual void Draw(const CRenderer &renderer, const ivec2 &position, float zRotation = 0.0f, const vec2 &scale = vec2(1.0f)) = 0;
};
