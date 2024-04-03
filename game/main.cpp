#include "CGame.h"

#if USE_MIMALLOC
#include "mimalloc-new-delete.h"
#endif
#include "SDL_main.h"

#if USE_MIMALLOC
extern "C" void* calloc(usize count, usize size)
{
    return mi_calloc(count, size);
}

extern "C" void *malloc(usize size)
{
    return calloc(1, size);
}

extern "C" void* realloc(void *block, usize size)
{
    return mi_realloc(block, size);
}

extern "C" void free(void* block)
{
    mi_free(block);
}

void __cdecl MiMallocStatsPrint(const char* message, void* userData)
{
    // remove trailing newline
    SPDLOG_DEBUG("{:.{}s}", message, strlen(message) - 1);
}
#endif

#ifdef SDL_PLATFORM_WINDOWS
void CreateOrAttachConsole()
{
    bool haveConsole = AttachConsole(ATTACH_PARENT_PROCESS);
    if (haveConsole
#ifdef GAME_DEBUG
        || (!haveConsole && AllocConsole())
#endif
    )
    {
        FILE *File;

        SPDLOG_DEBUG("Attaching console");

        freopen_s(&File, "CONIN$", "r", stdin);
        freopen_s(&File, "CONOUT$", "w", stdout);
        freopen_s(&File, "CONOUT$", "w", stderr);

        DWORD initialConsoleInputMode = 0;
        DWORD initialConsoleOutputMode = 0;
        DWORD initialConsoleErrorMode = 0;
#if _WIN32_WINNT >= 0x0A00
        GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &initialConsoleInputMode);
        SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), initialConsoleInputMode | ENABLE_VIRTUAL_TERMINAL_INPUT);

        GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &initialConsoleOutputMode);
        SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), initialConsoleOutputMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

        GetConsoleMode(GetStdHandle(STD_ERROR_HANDLE), &initialConsoleErrorMode);
        SetConsoleMode(GetStdHandle(STD_ERROR_HANDLE), initialConsoleErrorMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif

        // In case running under cmd.exe, to not be on same line as prompt.
        printf("\n");
    }
}
#endif

extern "C" s32 SDL_main(s32 argc, char *argv[])
{
    std::vector<std::string> args(argc);

    for (s32 i = 0; i < argc; i++)
    {
        args[i] = argv[i];
    }

    fs::path userDataRoot(SDL_GetPrefPath(GAME_ORGANIZATION, GAME_NAME));

#ifdef SDL_PLATFORM_WINDOWS
    CreateOrAttachConsole();
#endif

    constexpr u32 memoryReservation = 2;
#if USE_MIMALLOC
    SPDLOG_INFO("Using mimalloc allocator");
    mi_option_set(mi_option_reserve_huge_os_pages, memoryReservation);
    mi_option_set(mi_option_show_errors, TRUE);
#else
    SPDLOG_INFO("Using libc allocator");
    // Most allocators won't un-reserve memory, so freeing a big block should reserve some
    free(malloc(memoryReservation * 1024 * 1024 * 1024));
#endif

    CGame game(args, userDataRoot);
    s32 returnValue = game.Run();

#if USE_MIMALLOC
    mi_stats_print_out(MiMallocStatsPrint, nullptr);
#endif

    return returnValue;
}
