#pragma once

#include "shared.h"

#include "CSdlManager.h"

class CWindow
{
  public:
    CWindow(const std::string &title, u32 width, u32 height, u32 internalWidth = 512, u32 internalHeight = 384);
    ~CWindow();

    bool Update();
    void Present();

    const std::string &GetTitle()
    {
        return m_title;
    }

    u32 GetWidth()
    {
        return m_width;
    }

    u32 GetHeight()
    {
        return m_height;
    }

    void GetSize(u32 &width, u32 &height)
    {
        width = GetWidth();
        height = GetHeight();
    }

    u32 GetInternalWidth()
    {
        return m_internalWidth;
    }

    u32 GetInternalHeight()
    {
        return m_internalHeight;
    }

    void GetInternalSize(u32 &width, u32 &height)
    {
        width = GetInternalWidth();
        height = GetInternalHeight();
    }

    bool IsFocused()
    {
        return m_focused;
    }

    bool IsMinimized()
    {
        return m_minimized;
    }

    SDL_Window *GetRawWindow()
    {
        return m_window;
    }

    SDL_Renderer *GetRenderer()
    {
        return m_renderer;
    }

    SDL_Texture *GetRenderTarget()
    {
        return m_renderTarget;
    }

    void UseRenderTarget()
    {
        SDL_SetRenderTarget(m_renderer, m_renderTarget);
    }

    void UseBackbuffer()
    {
        SDL_SetRenderTarget(m_renderer, nullptr);
    }

  protected:
    SDL_Window *m_window;
    u32 m_windowId;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_renderTarget;

    std::string m_title;

    u32 m_width;
    u32 m_height;

    const u32 m_internalWidth;
    const u32 m_internalHeight;

    bool m_focused;
    bool m_minimized;
    bool m_closed;
};
