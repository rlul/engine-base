#pragma once
#include "core/ifilesystem.h"
#include <string>
#include <vector>
#include <fstream>

class CFileHandle
{
public:
	CFileHandle(std::fstream& p_file_stream, const char* path);
	~CFileHandle();

	void Close();
	const char* GetFilePath() const;
	unsigned int Read(void* buffer, unsigned int size);
	unsigned int Write(const void* buffer, unsigned int size);
	void Flush();
	void Seek(unsigned int size);
	unsigned int Tell();
	unsigned int Size();
	bool EndOfFile() const;

private:
	std::fstream m_FileStream;
	const char* m_pPath;
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
	virtual ~CFileSystem() override = default;

	virtual bool Setup(const char* absolute_game_path) override;
	virtual void Shutdown() override;
	virtual const char* GetSystemName() const override { return FILE_SYSTEM_VERSION; }

	virtual bool AddSearchPath(const char* path, const char* path_id) override;
	virtual const char* GetSearchPath(const char* path_id) const override;
	virtual void RemoveSearchPath(const char* path_id) override;

	virtual FileHandle_t Open(const char* file_name, const char* path_id, OpenFileOptions_t options) override;
	virtual FileHandle_t Open(const char* file_name, OpenFileOptions_t options) override;
	virtual FileHandle_t OpenFullPath(const char* file_path, OpenFileOptions_t options) override;
	virtual bool FileExists(const char* file_name, const char* path_id) override;
	virtual const char* GetFilePath(FileHandle_t file) override;
	virtual void Close(FileHandle_t file) override;

	virtual unsigned int Read(FileHandle_t file, void* buffer, unsigned int size) override;
	virtual unsigned int Write(FileHandle_t file, const void* buffer, unsigned int size) override;
	virtual void Flush(FileHandle_t file) override;
	virtual void Seek(FileHandle_t file, unsigned int position) override;
	virtual unsigned int Tell(FileHandle_t file) override;
	virtual unsigned int Size(FileHandle_t file) override;
	virtual bool EndOfFile(FileHandle_t file) override;

private:
	std::vector<CSearchPath*> m_SearchPaths;

};
