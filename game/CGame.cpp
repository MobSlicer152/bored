#include "CGame.h"

CGame::CGame(const std::vector<std::string> &args, const fs::path &userDataRoot)
    : CApplication(args, userDataRoot), m_running(false), m_renderer(m_window)
{
    SPDLOG_INFO("Initializing CGame with user data in {}", m_userData.GetRoot().generic_string());
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
        m_renderer.SetClearColor(vec4(0.4f, 0.0f, 1.0f, 1.0f));
        m_renderer.BeginFrame();
        m_renderer.DrawLine(vec2(0.0f), vec2(640.0f, 480.0f));
        m_renderer.EndFrame();

        m_running = m_window->Update();
    }
    SPDLOG_INFO("Exiting main loop");
}

CGame::~CGame()
{
    SPDLOG_INFO("Shutting down CGame");
}
