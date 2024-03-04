#include "common.h"

#include <string>
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
