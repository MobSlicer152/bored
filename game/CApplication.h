#pragma once

#include "shared.h"

#include "CPhysicalFilesystem.h"
#include "CWindow.h"

class CApplication
{
  public:
    CApplication() = delete;
    CApplication(const std::vector<std::string> &args, const fs::path &userDataRoot)
        : m_args(args), m_userData(userDataRoot, false)
    {
#ifdef GAME_DEBUG
        spdlog::set_level(spdlog::level::debug);
#endif
#ifdef SDL_PLATFORM_WINDOWS
        spdlog::default_logger()->sinks().push_back(std::make_shared<spdlog::sinks::msvc_sink_mt>(false));
#endif
        spdlog::default_logger()->sinks().push_back(
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>(spdlog::color_mode::automatic));
        spdlog::default_logger()->sinks().push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            m_userData.GetFullPath("logs/" GAME_EXECUTABLE_NAME ".log").generic_string(), SIZE_MAX, 3, true));
        spdlog::flush_every(chrono::seconds(3));

        m_window = std::make_shared<CWindow>(GAME_NAME, 1024, 768);
    }
    virtual s32 Run() = 0;
    virtual ~CApplication() = default;

  protected:
    std::vector<std::string> m_args;
    CPhysicalFilesystem m_userData;
    std::shared_ptr<CWindow> m_window;
};
