#pragma once

#include "shared.h"

#include "CWindow.h"
#include "IRenderable.h"

class CRenderer
{
  public:
    CRenderer(std::shared_ptr<CWindow> window) : m_window(window), m_clearColor(0.0f)
    {
    }
    ~CRenderer() = default;

    void BeginFrame();
    void EndFrame();

    vec4 SetClearColor(const vec4 &clearColor)
    {
        vec4 old = m_clearColor;
        m_clearColor = clearColor;
        return old;
    }

    void DrawLine(const vec2 &start, const vec2 &end, const vec4 &color = vec4(1.0f));

  private:
    std::shared_ptr<CWindow> m_window;
    vec4 m_clearColor;
};
