#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif

#if defined(_WIN32) && defined(ENGINE_EXPORTS)
#define ENGINE_API extern "C" __declspec(dllexport)
#elif defined(_WIN32) 
#define ENGINE_API extern "C" __declspec(dllimport)
#else
#define ENGINE_API
#endif


#ifdef _WIN32
ENGINE_API int EngineMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
#else
int EngineMain(int argc, char** argv);
#endif
