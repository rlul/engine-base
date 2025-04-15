#pragma once

#ifdef _WIN32
#define DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define DLL_EXPORT extern "C"
#endif

typedef void* module_t;
typedef void* symbol_t;

double COM_GetTime();

module_t COM_LoadModule(const char* module_name);
symbol_t COM_LoadSymbol(void* module, const char* name);
bool COM_GetGameDir(char* game_dir);
