#pragma once

#ifdef HZ_PLATFORM_WINDOWS
    #ifdef HZ_BUILD_LIB
        #define HAZEL_API __declspec(dllexport)
    #else
        #define HAZEL_API __declspec(dllimport)
    #endif
#elif HZ_PLATFORM_LINUX
    #ifdef HZ_BUILD_LIB
        #define HAZEL_API export
    #else
        #define HAZEL_API
    #endif
#endif