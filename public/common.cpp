#include "common.h"
#include "subsystems.h"
#include "core/icommandline.h"
#include <string>
#include <filesystem>

#include "core/ifilesystem.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

double GetStartTime()
{
#ifdef _WIN32
	FILETIME ft;
	static ULARGE_INTEGER t;
	if (!t.QuadPart)
	{
		GetSystemTimePreciseAsFileTime(&ft);
		t.LowPart = ft.dwLowDateTime;
		t.HighPart = ft.dwHighDateTime;
	}
	return t.QuadPart;
#else
	timespec tp;
	static double microseconds;
	if (!microseconds)
	{
		clock_gettime(CLOCK_MONOTONIC, &tp);
		microseconds = (double)tp.tv_sec * 1e6 + (double)tp.tv_nsec / 1e3;
	}
	return microseconds;
#endif
}

double COM_GetTime() 
{
#ifdef _WIN32
	constexpr int TICKS_PER_SECOND = 10000000;
	FILETIME ft;
	ULARGE_INTEGER t;

	GetSystemTimePreciseAsFileTime(&ft);
	t.LowPart = ft.dwLowDateTime;
	t.HighPart = ft.dwHighDateTime;
	return (static_cast<double>(t.QuadPart) - GetStartTime()) / TICKS_PER_SECOND;
#else
	constexpr int TICKS_PER_SECOND = 1000000;
	timespec tp;
	static double microseconds;
	clock_gettime(CLOCK_MONOTONIC, &tp);
	microseconds = (double)tp.tv_sec * 1e6 + (double)tp.tv_nsec / 1e3;
	return (microseconds - GetStartTime()) / TICKS_PER_SECOND;
#endif
}

module_t COM_LoadModule(const char* module_name)
{
	std::string path = module_name;
#ifdef _WIN32
	path = path + ".dll";
	return LoadLibraryA(path.c_str());
#else
	path = "lib" + path + ".so";
	return dlopen(path.c_str(), RTLD_NOW);
#endif
}

symbol_t COM_LoadSymbol(void* module, const char* name)
{
#ifdef _WIN32
	return GetProcAddress((HMODULE)module, name);
#else
	return dlsym(module, name);
#endif
}

bool COM_GetGameDir(char* game_dir)
{
	if (!game_dir)
		return false;
	if (!g_pCommandLine)
	{
		printf("COM_GetGameDir failed: " FILE_SYSTEM_VERSION " has not yet been connected!\n");
		return false;
	}
	if (g_pCommandLine->HasParam("game"))
	{
		std::filesystem::path game_path = g_pCommandLine->GetParam("game");
		if (!is_directory(game_path))
		{
			printf("COM_GetGameDir failed: Selected game directory does not exist.\n");
			return false;
		}
		if (!game_path.is_absolute())
		{
			game_path = absolute(game_path);
		}
		strcpy(game_dir, game_path.string().c_str());
		return true;
	}
	else
	{
		printf("COM_GetGameDir failed: Please set your -game parameter.\n");
		return false;
	}
	return false;
}
