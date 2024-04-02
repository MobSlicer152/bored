#include "CRenderer.h"

void CRenderer::BeginFrame()
{
    m_window->UseRenderTarget();
    SDL_SetRenderDrawColorFloat(m_window->GetRenderer(), m_clearColor.r, m_clearColor.g, m_clearColor.b,
                                m_clearColor.a);
    SDL_RenderClear(m_window->GetRenderer());
}

void CRenderer::EndFrame()
{
    m_window->Present();
}

void CRenderer::DrawLine(const vec2 &start, const vec2 &end, const vec4 &color)
{
    SDL_SetRenderDrawColorFloat(m_window->GetRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderLine(m_window->GetRenderer(), start.x, start.y, end.x, end.y);
}
