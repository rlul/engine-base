#ifdef _WIN32
#include <Windows.h>
#else

#endif

#ifdef _WIN32
extern "C" __declspec(dllexport) int EngineMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
extern "C" __attribute__((visibility("default"))) int EngineMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	int result = 0;

	MessageBoxA(0, 0, 0, 0);

	return result;
}

