#include "filesystem.h"
#include "subsystem.h"
#include <filesystem>
#include <cstring>

CFileSystem g_FileSystem;
CREATE_SINGLE_SYSTEM( CFileSystem, IFileSystem, FILE_SYSTEM_VERSION, g_FileSystem );

CFileHandle::CFileHandle(std::fstream& file_stream, const char* path)
	: m_FileStream(std::move(file_stream)), m_pPath(path)
{
	printf("Opened %s\n", m_pPath);
}

CFileHandle::~CFileHandle()
{
	delete[] m_pPath;
}

void CFileHandle::Close()
{
	if (m_FileStream && m_FileStream.is_open()) 
	{
		printf("Closing %s\n", m_pPath);
		m_FileStream.close();
	}
}

const char* CFileHandle::GetFilePath() const
{
	return m_pPath;
}

unsigned int CFileHandle::Read(void* buffer, unsigned int size)
{
	m_FileStream.read(static_cast<char*>(buffer), size);
	return m_FileStream.gcount();
}

unsigned int CFileHandle::Write(const void* buffer, unsigned int size)
{
	m_FileStream.write(static_cast<const char*>(buffer), size);
	return size;
}

void CFileHandle::Flush()
{
	m_FileStream.flush();
}

void CFileHandle::Seek(unsigned int size)
{
	m_FileStream.seekg(size);
}

unsigned int CFileHandle::Tell()
{
	return m_FileStream.tellg();
}

unsigned int CFileHandle::Size()
{
	std::streampos current_pos = m_FileStream.tellg();
	m_FileStream.seekg(0, std::ios::end);
	unsigned int size = m_FileStream.tellg();
	m_FileStream.seekg(current_pos);
	return size;
}

bool CFileHandle::EndOfFile() const
{
	return m_FileStream.eof();
}

bool CFileSystem::Setup(const char* absolute_game_path)
{
	std::string game_path = absolute_game_path;
	std::string core_path = std::filesystem::absolute(game_path + "/../core").string().c_str();
	AddSearchPath(core_path.c_str(), "core");
	AddSearchPath(game_path.c_str(), "game");
	return true;
}

void CFileSystem::Shutdown()
{
	for (const auto& p_search_path : m_SearchPaths)
	{
		delete p_search_path;
	}
	m_SearchPaths.clear();
}

bool CFileSystem::AddSearchPath(const char* path, const char* path_id)
{
	for (const auto & p_search_path : m_SearchPaths)
	{
		if (!strcmp(p_search_path->GetPathID(), path_id))
			return false;
	}
	CSearchPath* p_search_path = new CSearchPath(path, path_id);
	m_SearchPaths.push_back(p_search_path);
	return true;
}

const char* CFileSystem::GetSearchPath(const char* path_id) const
{
	for (const auto p_search_path : m_SearchPaths)
	{
		if (!strcmp(p_search_path->GetPathID(), path_id))
		{
			return p_search_path->GetPath();
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

FileHandle_t CFileSystem::Open(const char* file_name, const char* path_id, OpenFileOptions_t options)
{
	std::string full_path = std::string(GetSearchPath(path_id)) + '/' + file_name;

	return OpenFullPath(full_path.c_str(), options);
}

FileHandle_t CFileSystem::Open(const char* file_name, OpenFileOptions_t options)
{
	for (const auto& p_search_path : m_SearchPaths)
	{
		if (FileExists(file_name, p_search_path->GetPathID()))
		{
			return Open(file_name, p_search_path->GetPathID(), options);
		}
	}

	return nullptr;
}

FileHandle_t CFileSystem::OpenFullPath(const char* file_path, OpenFileOptions_t options)
{
	std::ios_base::openmode openMode = std::ios::binary;

	switch (options)
	{
	case OPEN_READ:
		openMode |= std::ios::in;
		break;
	case OPEN_WRITE:
		openMode |= std::ios::out;
		break;
	case OPEN_READ_WRITE:
		openMode |= std::ios::in | std::ios::out;
		break;
	default:
		return nullptr;
	}

	std::fstream file_stream(file_path, openMode);
	if (!file_stream.good())
	{
		return nullptr;
	}

	auto path_buffer = new char[strlen(file_path)];
	strcpy(path_buffer, file_path);

	return new CFileHandle(file_stream, path_buffer);
}

bool CFileSystem::FileExists(const char* file_name, const char* path_id)
{
	std::string file_path = std::string(GetSearchPath(path_id)) + '/' + file_name;
	std::ifstream file_stream(file_path);
	return file_stream.good();
}

const char* CFileSystem::GetFilePath(FileHandle_t file)
{
	if (!file) 
		return nullptr;

	return static_cast<CFileHandle*>(file)->GetFilePath();
}

void CFileSystem::Close(FileHandle_t file)
{
	if (!file) return;

	static_cast<CFileHandle*>(file)->Close();
	delete file;
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
