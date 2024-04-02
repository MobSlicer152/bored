#pragma once

#include "shared.h"

#include "CApplication.h"
#include "CMultiFilesystem.h"
#include "CPhysicalFilesystem.h"
#include "CRenderer.h"

class CGame : private CApplication
{
  public:
    CGame(const std::vector<std::string> &args, const fs::path &userDataRoot);
    s32 Run();
    ~CGame();

  private:
    bool m_running;
    CMultiFilesystem m_filesystem;
    CRenderer m_renderer;
    entt::registry m_registry;

    void Loop();
};
