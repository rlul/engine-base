#pragma once
#include "core/module.h"

abstract_class IFileSystem
{
public:
	virtual ~IFileSystem() = default;

	virtual bool AddSearchPath(const char* path) = 0;

	virtual const char* FindFirst(const char* filename) = 0;
};

CORE_API IFileSystem* FileSystem();