#pragma once

#if defined(_WIN32) && defined(BASE_EXPORTS)
#define BASE_API extern "C" __declspec(dllexport)
#elif defined(_WIN32) 
#define BASE_API extern "C" __declspec(dllimport)
#else
#define BASE_API
#endif
