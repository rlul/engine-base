#include "filesystem.h"
#include "subsystem.h"

CFileSystem g_FileSystem;
CREATE_SINGLE_SYSTEM( CFileSystem, IFileSystem, FILE_SYSTEM_VERSION, g_FileSystem );

unsigned int CFileHandle::Read(void* buffer, unsigned int size)
{
	return 0;
}

unsigned int CFileHandle::Write(const void* buffer, unsigned int size)
{
	return 0;
}

void CFileHandle::Flush()
{
	return;
}

void CFileHandle::Seek(unsigned int size)
{
	return;
}

unsigned int CFileHandle::Tell()
{
	return 0;
}

unsigned int CFileHandle::Size()
{
	return 0;
}

bool CFileHandle::EndOfFile()
{
	return true;
}

bool CFileHandle::IsOk()
{
	return false;
}

void CFileSystem::Shutdown()
{
	for (const auto pSearchPath : m_SearchPaths)
	{
		delete pSearchPath;
	}
	m_SearchPaths.clear();
}

bool CFileSystem::AddSearchPath(const char* path, const char* path_id)
{
	// TODO: Should check if the path already exists
	CSearchPath* pSearchPath = new CSearchPath(path, path_id);
	m_SearchPaths.push_back(pSearchPath);
	return true;
}

const char* CFileSystem::GetSearchPath(const char* path_id) const
{
	for (const auto pSearchPath : m_SearchPaths)
	{
		if (pSearchPath->GetPathID() == path_id)
		{
			return pSearchPath->GetPath();
		}
	}
	return nullptr;
}

void CFileSystem::RemoveSearchPath(const char* path_id)
{
	for (auto it = m_SearchPaths.begin(); it != m_SearchPaths.end(); ++it)
	{
		if ((*it)->GetPathID() == path_id)
		{
			delete *it;
			m_SearchPaths.erase(it);
			break;
		}
	}
}

FileHandle_t CFileSystem::Open(const char* file_name, const char* path_id, const char* options)
{
	return nullptr;
}

bool CFileSystem::FileExists(const char* file_name, const char* path_id)
{
	return false;
}

void CFileSystem::Close(FileHandle_t file)
{
	
}

unsigned int CFileSystem::Read(FileHandle_t file, void* buffer, unsigned size)
{
	if (!file) return 0;

	return static_cast<CFileHandle*>(file)->Read(buffer, size);
}

unsigned int CFileSystem::Write(FileHandle_t file, const void* buffer, unsigned size)
{
	if (!file) return 0;

	return static_cast<CFileHandle*>(file)->Write(buffer, size);
}

void CFileSystem::Flush(FileHandle_t file)
{
	if (!file) return;

	static_cast<CFileHandle*>(file)->Flush();
}

void CFileSystem::Seek(FileHandle_t file, unsigned int position)
{
	if (!file) return;

	static_cast<CFileHandle*>(file)->Seek(position);
}

unsigned int CFileSystem::Tell(FileHandle_t file)
{
	if (!file) return 0;

	return static_cast<CFileHandle*>(file)->Tell();
}

unsigned int CFileSystem::Size(FileHandle_t file)
{
	if (!file) return 0;

	return static_cast<CFileHandle*>(file)->Size();
}

bool CFileSystem::EndOfFile(FileHandle_t file)
{
	if (!file) return true;

	return static_cast<CFileHandle*>(file)->EndOfFile();
}

bool CFileSystem::IsOk(FileHandle_t file)
{
	if (!file) return false;

	static_cast<CFileHandle*>(file)->IsOk();
}
