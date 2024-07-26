#pragma once

#ifdef HZ_ENABLE_ASSERTS
#define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define HZ_ASSERT
#define HZ_CORE_ASSERT
#endif

#define HZ_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#define BIT(x) (1 << x)