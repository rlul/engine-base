#pragma once
#include "module.h"
#include <string>

abstract_class ICommandLine
{
public:
	/**
	 * \brief Parses the command line from a string.
	 * \param cmdline The input command line string.
	 */
	virtual void Create(const char* cmdline) = 0;
	/**
	 * \brief Initializes the parser from command line arguments.
	 * \param argc
	 * \param argv
	 */
	virtual void Create(int argc, char** argv) = 0;
	/**
	 * \brief Gets the original command line string.
	 * \return Original command line string, or NULL if not initialized.
	 */
	virtual const char* Get() const = 0;

	/**
	 * \brief Checks if a parameter exists.
	 * \param param String name of the parameter.
	 * \return true if the parameter is present, or false if not.
	 */
	virtual bool HasParam(const char* param) const = 0;

	/**
	 * \brief Gets parameter value.
	 * \param param String name of the parameter.
	 * \return String value specified after the parameter, or NULL if no value is present.
	 */
	virtual const char* GetParam(const char* param) const = 0;
	int GetParamInt(const char* param) const { return std::stoi(std::string(GetParam(param))); }
};

CORE_API ICommandLine* CommandLine();
