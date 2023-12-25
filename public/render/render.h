#pragma once

#if defined(_WIN32) 
#if defined(RENDER_EXPORTS)
#define RENDER_API extern "C" __declspec(dllexport)
#else
#define RENDER_API extern "C" __declspec(dllimport)
#endif
#else
#define RENDER_API
#endif
