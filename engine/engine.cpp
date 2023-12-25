#include "engine/engine.h"

#include <iostream>

#ifdef _WIN32
int EngineMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int EngineMain(int argc, char **argv)
#endif
{
	int result = 0;

	printf("123\n");

	return result;
}

