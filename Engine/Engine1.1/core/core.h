#ifndef CORE_H
#define CORE_H

#ifdef PLATFORM_WINDOWS
#ifdef BUILD_DLL
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif // BUILD_DLL
#endif // PLATFORM_WINDOWS

#endif // !CORE_H
