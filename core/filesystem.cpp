#include "core/ifilesystem.h"

class CFileSystem : public IFileSystem
{
public:
	CFileSystem();
	~CFileSystem();

	bool AddSearchPath(const char* path) override;

	const char* FindFirst(const char* filename) override;
};

CFileSystem g_FileSystem;
IFileSystem* FileSystem()
{
	return &g_FileSystem;
}

CFileSystem::CFileSystem()
{
}

CFileSystem::~CFileSystem()
{
}

bool CFileSystem::AddSearchPath(const char* path)
{
	return false;
}

const char* CFileSystem::FindFirst(const char* filename)
{
	return 0;
}
