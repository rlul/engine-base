#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
#include <string>
#include <filesystem>

#ifdef _WIN32
typedef int (*EngineMain_t)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
#else
typedef int (*EngineMain_t)(int argc, char **argv);
#endif

#ifdef _WIN32
std::string GetBaseDir(std::string_view path)
{
	std::filesystem::path base_path(path);

	if (is_directory(base_path)) {
		return {};
	}

	return base_path.parent_path().generic_string();
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char module_path[MAX_PATH];
	std::string engine_path;
	HINSTANCE engine_module;
	EngineMain_t engine_main;

	GetModuleFileName(hInstance, module_path, MAX_PATH);
	engine_path = GetBaseDir(module_path).append("/bin/engine.dll");
	engine_module = LoadLibraryEx(engine_path.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	if (!engine_module)
	{
		MessageBoxA(0, "Failed to load engine library.", 0, 0);
		return 0;
	}

	engine_main = reinterpret_cast<EngineMain_t>(GetProcAddress(engine_module, "EngineMain"));
    if (!engine_main)
    {
        MessageBoxA(0, "Failed to load engine entry point.", 0, 0);
    }

	return engine_main(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}
#else
int main(int argc, char** argv)
{
    void* engine_module;
    EngineMain_t engine_main;

    engine_module = dlopen("bin/libengine.so", RTLD_NOW);
    if (!engine_module)
    {
        printf("Failed to load engine library. (%s)\n", dlerror());
        return 0;
    }

    engine_main = (EngineMain_t)dlsym(engine_module, "EngineMain");
    if (!engine_main)
    {
        printf("Failed to load engine entry point. (%s)\n", dlerror());
        return 0;
    }

	return engine_main(argc, argv);
}
#endif