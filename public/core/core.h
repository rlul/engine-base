#pragma once

#if defined(_WIN32) && defined(CORE_EXPORTS)
#define CORE_API extern "C" __declspec(dllexport)
#elif defined(_WIN32) 
#define CORE_API extern "C" __declspec(dllimport)
#else
#define CORE_API
#endif
