add_rules("plugin.vsxmake.autoupdate")

set_project("game")
set_version("0.0.0", {build = "%Y%m%d%H%M"})

if is_host("windows") then
    set_allowedmodes("debug-gdk", "debug-xbox", "debug-xp", "release-gdk", "release-xbox", "release-xp")
else
    set_allowedmodes("debug", "release")
end

if is_mode("debug", "debug-gdk", "debug-xbox", "debug-xp") then
    add_defines("GAME_DEBUG=1")
    set_optimize("none")
    set_symbols("debug")
else
    add_defines("GAME_RELEASE=1")
    set_optimize("fastest")
    set_symbols("hidden")
end
set_strip("all")

if is_mode("debug-gdk", "release-gdk") then
    add_defines("_GAMING_DESKTOP")
elseif is_mode("debug-xbox", "release-xbox") then
    add_defines("_GAMING_XBOX_SCARLETT")
elseif is_mode("debug-xp", "release-xp") then
    add_defines("_WIN32_WINVER=0x501")
end

set_languages("cxxlatest")
set_exceptions("cxx")

add_defines("USE_MIMALLOC=1")

add_repositories("local-repo xmake")
add_requires(
    "box2d",
    "entt",
    "fmt",
    "glm",
    "imgui_sdl3",
    "libsdl3",
    "mimalloc",
    "qoi",
    "spdlog",
    "stb",
    "xxhash",
    "zstd"
)

add_includedirs(
    "$(scriptdir)",
    path.absolute(path.join("$(buildir)", "config"))
)

target("game")
    set_kind("binary")
    add_headerfiles(path.join("game", "**.h*"))
    add_files(path.join("game", "**.cpp"))

    set_configdir(path.join("$(buildir)", "config"))
    add_configfiles("game/config.h.in")

    add_packages(
        "box2d",
        "entt",
        "fmt",
        "glm",
        "imgui_sdl3",
        "libsdl3",
        "mimalloc",
        "qoi",
        "spdlog",
        "stb",
        "xxhash",
        "zstd"
    )
target_end()
