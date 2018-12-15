#pragma once

#include <array>
#include <string>

#ifdef _MSC_VER
#include <windows.h>
#endif

namespace eng
{
    enum class LogLevel
    {
        Info = 0,
        Error
    };

    template <typename... Args>
    void shoeLog(eng::LogLevel level, const char* format, Args... args)
    {
        std::FILE* output = (level == LogLevel::Info ? stdout : stderr);
        std::fprintf(output, format, args...);
        std::fprintf(output, "\n");

#ifdef _MSC_VER
        char buffer[512]; \
        sprintf_s(buffer, sizeof(buffer), format, args...); \
        OutputDebugStringA(buffer);
        OutputDebugStringA("\n");
#endif
    }
}

#define SHOE_LOG(format, ...) \
        do { \
        eng::shoeLog(eng::LogLevel::Info, "[%s:%d] " format, __FILE__, __LINE__, ##__VA_ARGS__); } \
        while (false)

#define SHOE_LOG_ERROR(format, ...) \
        do { \
        eng::shoeLog(eng::LogLevel::Error, "[%s:%d] ERROR: " format, __FILE__, __LINE__, ##__VA_ARGS__); } \
        while (false)