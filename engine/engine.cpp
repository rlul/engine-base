#ifdef _WIN32
#include <Windows.h>
#else

#endif
#include <iostream>

#ifdef _WIN32
int EngineMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
               int nCmdShow)
#else
int EngineMain(int argc, char **argv)
#endif
{
  int result = 0;

  printf("123\n");

#ifdef _WIN32
  MessageBoxA(0, 0, 0, 0);
#endif

  return result;
}
