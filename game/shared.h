#pragma once

#include "config.h"

#include "SDL_platform_defines.h"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <ios>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "entt/entt.hpp"

#include "fmt/format.h"

#include "glm/glm.hpp"
using namespace glm;

#include "qoi.h"

#include "SDL.h"

#ifdef GAME_DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#endif
#ifdef _MSC_VER
#define SPDLOG_FUNCTION static_cast<const char *>(__FUNCSIG__)
#else
#define SPDLOG_FUNCTION static_cast<const char *>(__PRETTY_FUNCTION__)
#endif
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#if defined SDL_PLATFORM_WINDOWS
#include "spdlog/sinks/msvc_sink.h"
#elif defined SDL_PLATFORM_ANDROID
#include "spdlog/sinks/android_sink.h"
#endif

namespace chrono = std::chrono;
namespace fs = std::filesystem;

using s8 = std::uint8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using byte = u8;

using sptr = std::intptr_t;
using uptr = std::uintptr_t;

using ssize = sptr;
using usize = uptr;
