#pragma once

#include "shared.h"

struct CSdlManager
{
  public:
    static CSdlManager &GetInstance()
    {
        static CSdlManager s_instance;
        return s_instance;
    }

    // TODO: idOffset is a terrible idea, but I guess it should be fine cause the ABI is mostly stable
    void GetEvents(std::vector<SDL_Event> &events, u32 id, SDL_EventType first = SDL_EVENT_WINDOW_FIRST,
                   SDL_EventType last = SDL_EVENT_WINDOW_LAST, u64 idOffset = 16);

    CSdlManager(const CSdlManager &other) = delete;
    void operator=(const CSdlManager &Other) = delete;

  protected:
    CSdlManager()
    {
    }
};