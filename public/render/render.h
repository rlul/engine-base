#pragma once

#if defined(RENDER_EXPORTS) && defined(_WIN32) 
#define RENDER_API extern "C" __declspec(dllexport)
#else
#define RENDER_API extern "C" __declspec(dllimport)
#endif
