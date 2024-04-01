#pragma once

#include "shared.h"

#include "CApplication.h"

class CGame : private CApplication
{
  public:
    CGame(const std::vector<std::string> &args, const fs::path &userDataRoot);
    s32 Run();
    ~CGame();

  private:
    bool m_running;

    void Loop();
};
