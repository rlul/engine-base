#include "common.h"
#include "base/icommandline.h"
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
			game_dir = CommandLine()->GetParam<std::string>("game");
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
