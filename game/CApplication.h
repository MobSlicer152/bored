#pragma once

#include "shared.h"

#include "CWindow.h"

class CApplication
{
  public:
    CApplication() = delete;
    CApplication(const std::vector<std::string> &args, const fs::path &userDataRoot)
        : m_args(args), m_userDataRoot(userDataRoot), m_window(GAME_NAME, 1024, 768)
    {
#ifdef GAME_DEBUG
        spdlog::set_level(spdlog::level::debug);
#endif
#ifdef SDL_PLATFORM_WINDOWS
        spdlog::default_logger()->sinks().push_back(std::make_shared<spdlog::sinks::msvc_sink_mt>(false));
#endif
        spdlog::default_logger()->sinks().push_back(
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>(spdlog::color_mode::automatic));
    }
    virtual s32 Run() = 0;
    virtual ~CApplication() = default;

  protected:
    std::vector<std::string> m_args;
    fs::path m_userDataRoot;
    CWindow m_window;
};
