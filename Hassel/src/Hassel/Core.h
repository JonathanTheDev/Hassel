#pragma once


#ifdef HASSEL_PLATFORM_WINDOWS

#ifdef HASSEL_BUILD_DLL
#define HASSEL_API __declspec(dllexport)
#else
#define HASSEL_API __declspec(dllimport)
#endif // HASSEL_BUILD_DLL

#else
#error Hassel only support Windows!
#endif // HASSEL_PLATFORM_WINDOWS

#ifdef HSL_DEBUG
#define HSL_ENABLE_ASSERTS
#endif

#ifdef HSL_ENABLE_ASSERTS
#define HSL_ASSERT(x, ...) { if(!(x)) { HSL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HSL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define HSL_ASSERT(x, ...)
#define HZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HSL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)