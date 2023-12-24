#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef ENGINE_EXPORTS
#define ENGINE_API extern "C" __declspec(dllexport)
#else
#define ENGINE_API extern "C" __declspec(dllimport)
#endif

#ifdef _WIN32
ENGINE_API int EngineMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
#else
int EngineMain(int argc, char** argv);
#endif
