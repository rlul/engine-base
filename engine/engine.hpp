#ifdef _WIN32
int EngineMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
               int nCmdShow);
#else
int EngineMain(int argc, char **argv);
#endif
