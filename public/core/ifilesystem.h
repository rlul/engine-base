#pragma once
#include "subsystems.h"

#define FILE_SYSTEM_VERSION "FileSystem001"

typedef void* FileHandle_t;

abstract_class IFileSystem : public IAppSystem
{
public:
	enum OpenFileOptions_t
	{
		OPEN_READ = 0,
		OPEN_WRITE,
		OPEN_READ_WRITE
	};

public:
	virtual ~IFileSystem() = default;

	virtual bool Setup(const char* game_path) = 0;

	virtual bool AddSearchPath(const char* path, const char* path_id) = 0;
	virtual const char* GetSearchPath(const char* path_id) const = 0;
	virtual void RemoveSearchPath(const char* path_id) = 0;

	/**
	 * \brief 
	 * \param file_name 
	 * \param path_id 
	 * \param options 
	 * \return Handle to the file if successful, nullptr otherwise.
	 */
	virtual FileHandle_t Open(const char* file_name, const char* path_id, OpenFileOptions_t options) = 0;
	/**
	 * \brief (Gives priority to the first file path in the list.)
	 * \param file_name 
	 * \param options 
	 * \return Handle to the file if successful, nullptr otherwise.
	 */
	virtual FileHandle_t Open(const char* file_name, OpenFileOptions_t options) = 0;
	virtual bool FileExists(const char* file_name, const char* path_id) = 0;
	virtual void Close(FileHandle_t file) = 0;

	/**
	 * \brief Reads from the file
	 * \param file 
	 * \param buffer 
	 * \param size 
	 * \return The number of bytes read
	 */
	virtual unsigned int Read(FileHandle_t file, void* buffer, unsigned int size) = 0;
	/**
	 * \brief Writes to the file
	 * \param file 
	 * \param buffer 
	 * \param size 
	 * \return The number of bytes written
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
	 * \return The current position in the file
	 */
	virtual unsigned int Tell(FileHandle_t file) = 0;
	/**
	 * \param file 
	 * \return The size of the file in bytes
	 */
	virtual unsigned int Size(FileHandle_t file) = 0;
	/**
	 * \param file 
	 * \return True if the end of the file has been reached
	 */
	virtual bool EndOfFile(FileHandle_t file) = 0;
};
