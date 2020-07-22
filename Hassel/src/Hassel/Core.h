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
