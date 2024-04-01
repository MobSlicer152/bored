#include "CWindow.h"

CWindow::CWindow(const std::string &title, u32 width, u32 height, u32 internalWidth, u32 internalHeight)
    : m_title(title), m_width(width), m_height(height), m_internalWidth(internalWidth),
      m_internalHeight(internalHeight), m_closed(false), m_minimized(false), m_focused(false)
{
    SPDLOG_INFO("Creating {}x{} window titled {} with internal size {}x{}", width, height, title, internalWidth,
                internalHeight);

    if (SDL_CreateWindowAndRenderer(m_width, m_height, SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_RESIZABLE, &m_window, &m_renderer) < 0)
    {
        SPDLOG_CRITICAL("Failed to create window: {}", SDL_GetError());
        std::terminate();
    }

    m_windowId = SDL_GetWindowID(m_window);

    SDL_SetWindowTitle(m_window, m_title.c_str());

    m_surface = SDL_CreateSurface(m_internalWidth, m_internalHeight, SDL_PIXELFORMAT_RGBA8888);
    if (!m_surface)
    {
        SPDLOG_CRITICAL("Failed to create window internal surface: {}", SDL_GetError());
        std::terminate();
    }

    SDL_ShowWindow(m_window);
}

CWindow::~CWindow()
{
    SDL_DestroySurface(m_surface);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

bool CWindow::Update()
{
    if (m_closed)
    {
        return false;
    }

    std::vector<SDL_Event> events;
    CSdlManager::GetInstance().GetEvents(events, m_windowId);

    for (const auto &event : events)
    {
        switch (event.type)
        {
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            SPDLOG_INFO("Window {} closed", m_title);
            m_closed = true;
            break;
        case SDL_EVENT_WINDOW_RESIZED:
            if (m_width != event.window.data1 || m_height != event.window.data2)
            {
                SPDLOG_INFO("Window resized from {}x{} to {}x{}", m_width, m_height, event.window.data1,
                            event.window.data2);
                m_width = event.window.data1;
                m_height = event.window.data2;
            }
            break;
        case SDL_EVENT_WINDOW_FOCUS_GAINED:
            SPDLOG_INFO("Window {} focused", m_title);
            m_focused = true;
            break;
        case SDL_EVENT_WINDOW_FOCUS_LOST:
            SPDLOG_INFO("Window {} unfocused", m_title);
            m_focused = false;
            break;
        case SDL_EVENT_WINDOW_MINIMIZED:
            SPDLOG_INFO("Window {} minimized", m_title);
            m_minimized = true;
            break;
        case SDL_EVENT_WINDOW_RESTORED:
            SPDLOG_INFO("Window {} restored", m_title);
            m_minimized = false;
            break;
        }
    }

    return !m_closed;
}