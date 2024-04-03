#include "CGame.h"

CGame::CGame(const std::vector<std::string> &args, const fs::path &userDataRoot)
    : CApplication(args, userDataRoot), m_running(false), m_renderer(std::make_shared<CRenderer>(m_window)),
      m_filesystem(std::make_shared<CMultiFilesystem>())
{
    SPDLOG_INFO("Initializing CGame with user data in {}", m_userData->GetRoot().generic_string());

    m_filesystem->AddFilesystem(std::make_shared<CPhysicalFilesystem>(fs::path("assets")));
}

s32 CGame::Run()
{
    m_running = true;
    Loop();

    return 0;
}

void CGame::Loop()
{
    CImage test(m_renderer, *m_filesystem, fs::path("test.qoi"));

    SPDLOG_INFO("Entering main loop");
    while (m_running)
    {
        m_renderer->SetClearColor(vec4(0.4f, 0.0f, 1.0f, 1.0f));
        m_renderer->BeginFrame();
        test.Draw(ivec2(0));
        m_renderer->EndFrame();

        m_running = m_window->Update();
    }
    SPDLOG_INFO("Exiting main loop");
}

CGame::~CGame()
{
    SPDLOG_INFO("Shutting down CGame");
}
