#pragma once
#include "subsystems.h"

#define FILE_SYSTEM_VERSION "FileSystem001"

typedef void* FileHandle_t;

abstract_class IFileSystem : public IAppSystem
{
public:
	virtual ~IFileSystem() = default;

	virtual bool AddSearchPath(const char* absolute_path, const char* path_id) = 0;
	virtual const char* GetSearchPath(const char* path_id) const = 0;
	virtual void RemoveSearchPath(const char* path_id) = 0;

	virtual FileHandle_t Open(const char* file_name, const char* path_id, const char* options) = 0;
	virtual bool FileExists(const char* file_name, const char* path_id) = 0;
	virtual void Close(FileHandle_t file) = 0;

	/**
	 * \brief Reads from the file
	 * \param file 
	 * \param buffer 
	 * \param size 
	 * \return the number of bytes read
	 */
	virtual unsigned int Read(FileHandle_t file, void* buffer, unsigned int size) = 0;
	/**
	 * \brief Writes to the file
	 * \param file 
	 * \param buffer 
	 * \param size 
	 * \return the number of bytes written
	 */
	virtual unsigned int Write(FileHandle_t file, const void* buffer, unsigned int size) = 0;
	/**
	 * \brief Flushes the file
	 * \param file 
	 */
	virtual void Flush(FileHandle_t file) = 0;
	/**
	 * \brief Changes the current position in the file
	 * \param file 
	 * \param position 
	 */
	virtual void Seek(FileHandle_t file, unsigned int position) = 0;
	/**
	 * \param file 
	 * \return the current position in the file
	 */
	virtual unsigned int Tell(FileHandle_t file) = 0;
	/**
	 * \param file 
	 * \return the size of the file in bytes
	 */
	virtual unsigned int Size(FileHandle_t file) = 0;
	/**
	 * \param file 
	 * \return true if the end of the file has been reached
	 */
	virtual bool EndOfFile(FileHandle_t file) = 0;
	virtual bool IsOk(FileHandle_t file) = 0;
};
