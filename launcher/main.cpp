#include "engine/module.h"

#ifdef _WIN32
#include <Windows.h>
#endif
#include <string>
#include <filesystem>

#ifdef _WIN32
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	return EngineMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}
#else
int main(int argc, char** argv)
{
	return EngineMain(argc, argv);
}
#endif