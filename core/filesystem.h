#pragma once
#include "core/ifilesystem.h"
#include <string>
#include <vector>

class CFileHandle
{
public:
	CFileHandle() = default;
	~CFileHandle() = default;

	unsigned int Read(void* buffer, unsigned int size);
	unsigned int Write(const void* buffer, unsigned int size);
	void Flush();
	void Seek(unsigned int size);
	unsigned int Tell();
	unsigned int Size();
	bool EndOfFile();
	bool IsOk();

private:

};

class CSearchPath
{
public:
	CSearchPath(const char* path, const char* path_id)
		: m_Path(path), m_PathID(path_id)
	{
		
	}
	~CSearchPath() = default;

	const char* GetPath() const { return m_Path.c_str(); }
	const char* GetPathID() const { return m_PathID.c_str(); }

private:
	std::string m_Path;
	std::string m_PathID;
};

class CFileSystem : public IFileSystem
{
public:
	CFileSystem() = default;
	~CFileSystem() override = default;

	void Shutdown() override;
	const char* GetSystemName() const override { return FILE_SYSTEM_VERSION; }

	bool AddSearchPath(const char* path, const char* path_id) override;
	const char* GetSearchPath(const char* path_id) const override;
	void RemoveSearchPath(const char* path_id) override;

	FileHandle_t Open(const char* file_name, const char* path_id, const char* options) override;
	bool FileExists(const char* file_name, const char* path_id) override;
	void Close(FileHandle_t file) override;

	unsigned int Read(FileHandle_t file, void* buffer, unsigned int size) override;
	unsigned int Write(FileHandle_t file, const void* buffer, unsigned int size) override;
	void Flush(FileHandle_t file) override;
	void Seek(FileHandle_t file, unsigned int position) override;
	unsigned int Tell(FileHandle_t file) override;
	unsigned int Size(FileHandle_t file) override;
	bool EndOfFile(FileHandle_t file) override;
	bool IsOk(FileHandle_t file) override;

private:
	std::vector<CSearchPath*> m_SearchPaths;

};
