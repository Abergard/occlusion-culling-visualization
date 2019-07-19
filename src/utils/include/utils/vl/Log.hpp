#pragma once

#include <vlCore/Log.hpp>
#include <vlCore/Say.hpp>

namespace ocv
{
#define Log(Severity, Msg)                                  \
    do                                                      \
    {                                                       \
        vl::Log::print(vl::Say("[%s] %s(%s): %s\n")         \
                       << Severity << __FUNCTION__          \
                       << std::to_string(__LINE__) << Msg); \
    } while (0);

#define Info(Msg)         \
    do                    \
    {                     \
        Log("Info", Msg); \
    } while (0);

#define Debug(Msg)         \
    do                     \
    {                      \
        Log("Debug", Msg); \
    } while (0);

#define Error(Msg)         \
    do                     \
    {                      \
        Log("Error", Msg); \
    } while (0);

#define Trace()           \
    do                    \
    {                     \
        Log("Trace", ""); \
    } while (0);
} // namespace ocv
