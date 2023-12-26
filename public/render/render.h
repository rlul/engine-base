#pragma once

#if defined(_WIN32) && defined(RENDER_EXPORTS)
#define RENDER_API extern "C" __declspec(dllexport)
#elif defined(_WIN32) 
#define RENDER_API extern "C" __declspec(dllimport)
#else
#define RENDER_API
#endif
