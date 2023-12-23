#ifdef _WIN32
#include <Windows.h>
#else

#endif
#include <string>
#include <filesystem>

#ifdef _WIN32
typedef int (*EngineMain_t)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
#else
typedef int (*EngineMain_t)(int argc, char **argv);
#endif

std::string GetBaseDir(std::string_view path)
{
	std::filesystem::path base_path(path);

	if (is_directory(base_path)) {
		return {};
	}

	return base_path.parent_path().generic_string();
}

#ifdef _WIN32
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char module_path[MAX_PATH];
	std::string engine_path;
	HINSTANCE engine;
	EngineMain_t engine_main;

	GetModuleFileName(hInstance, module_path, MAX_PATH);
	engine_path = GetBaseDir(module_path).append("/bin/engine.dll");
	engine = LoadLibraryEx(engine_path.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

	if (engine == NULL)
	{
		MessageBoxA(0, "Couldn't load engine library.", "Error", 0);
		return 0;
	}

	engine_main = reinterpret_cast<EngineMain_t>(GetProcAddress(engine, "EngineMain"));

	return engine_main(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}
#else
int main(int argc, char** argv)
{

	return 0;
}
#endif