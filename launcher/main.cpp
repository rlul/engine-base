#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

#include "../engine/engine.hpp"

#ifdef _WIN32
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nCmdShow) {
  return EngineMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}
#else
int main(int argc, char **argv) { return EngineMain(argc, argv); }
#endif