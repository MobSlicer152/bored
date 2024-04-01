#include "CGame.h"

#include "SDL_main.h"

extern "C" s32 main(s32 argc, char *argv[])
{
    std::vector<std::string> args(argc);

    for (s32 i = 0; i < argc; i++)
    {
        args[i] = argv[i];
    }

    fs::path userDataRoot(SDL_GetPrefPath(GAME_ORGANIZATION, GAME_NAME));

    CGame game(args, userDataRoot);
    return game.Run();
}
