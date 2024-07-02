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

#ifdef HZ_ENABLE_ASSERTS
#define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define HZ_ASSERT
#define HZ_CORE_ASSERT
#endif

#define BIT(x) (1 << x)