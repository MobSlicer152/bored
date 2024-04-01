#include "CGame.h"

CGame::CGame(const std::vector<std::string> &args, const fs::path &userDataRoot)
    : CApplication(args, userDataRoot), m_running(false)
{
    SPDLOG_INFO("Initializing CGame with user data in {}", m_userDataRoot.generic_string());
}

s32 CGame::Run()
{
    m_running = true;
    Loop();

    return 0;
}

void CGame::Loop()
{
    SPDLOG_INFO("Entering main loop");
    while (m_running)
    {
        m_running = m_window.Update();
    }
    SPDLOG_INFO("Exiting main loop");
}

CGame::~CGame()
{
    SPDLOG_INFO("Shutting down CGame");
}
