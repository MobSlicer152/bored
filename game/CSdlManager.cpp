#include "CSdlManager.h"

void CSdlManager::GetEvents(std::vector<SDL_Event> &events, u32 id, SDL_EventType first, SDL_EventType last,
                            u64 idOffset)
{
    std::vector<SDL_Event> unrelated;

    if (idOffset + sizeof(u32) > sizeof(SDL_Event))
    {
        return;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type > first && event.type < last && *(u32 *)((u8 *)&event + idOffset) == id)
        {
            events.push_back(event);
        }
        else
        {
            unrelated.push_back(event);
        }
    }

    for (SDL_Event event : unrelated)
    {
        SDL_PushEvent(&event);
    }
}