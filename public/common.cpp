#include "common.h"
#include "core/icommandline.h"
#include <filesystem>
#include <cassert>
#ifdef _WIN32
#include <Windows.h>
#else

#endif


std::string COM_GetGameDir()
{
	static std::filesystem::path game_dir;
	
	if (game_dir.empty())
	{
		if (CommandLine()->HasParam("game"))
		{
			game_dir = CommandLine()->GetParam("game");
			if (!game_dir.is_absolute())
			{
				game_dir = absolute(game_dir);
			}
		}
		else
		{
#ifdef _WIN32
			char module_path[MAX_PATH];
			GetModuleFileName(NULL, module_path, MAX_PATH);
			game_dir = module_path;
#else
			game_dir = std::filesystem::canonical("/proc/self/exe");
#endif
			game_dir = canonical(game_dir.parent_path().append("../../" GAME_NAME));
		}
		assert(exists(game_dir));
	}

	return game_dir.string();
}

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
