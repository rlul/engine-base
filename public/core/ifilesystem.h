#pragma once
#include "core.h"

abstract_class IFileSystem
{
public:
	virtual bool AddSearchPath(const char* path) = 0;

	virtual const char* FindFirst(const char* filename) = 0;
};

CORE_API IFileSystem* FileSystem();