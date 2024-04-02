#include "CRenderer.h"

void CRenderer::BeginFrame()
{
    m_window->UseRenderTarget();
    SDL_SetRenderDrawColorFloat(GetRenderer(), m_clearColor.r, m_clearColor.g, m_clearColor.b,
                                m_clearColor.a);
    SDL_RenderClear(GetRenderer());
}

void CRenderer::EndFrame()
{
    m_window->Present();
}

void CRenderer::DrawLine(const vec2 &start, const vec2 &end, const vec4 &color)
{
    SDL_SetRenderDrawColorFloat(GetRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderLine(GetRenderer(), start.x, start.y, end.x, end.y);
}
