#pragma once

#include "shared.h"

#include "CApplication.h"
#include "CImage.h"
#include "CSprite.h"
#include "CSpriteSheet.h"
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
    std::shared_ptr<CMultiFilesystem> m_filesystem;
    std::shared_ptr<CRenderer> m_renderer;
    entt::registry m_registry;

    void Loop();
};
