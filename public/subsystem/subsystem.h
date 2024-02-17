#pragma once

#if defined(_WIN32) && defined(SUBSYSTEM_EXPORTS)
#define SUBSYSTEM_API extern "C" __declspec(dllexport)
#elif defined(_WIN32) 
#define SUBSYSTEM_API extern "C" __declspec(dllimport)
#else
#define SUBSYSTEM_API
#endif
