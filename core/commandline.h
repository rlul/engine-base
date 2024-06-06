#pragma once
#include "core/icommandline.h"
#include <string>
#include <vector>
#include <map>

class CCommandLine : public ICommandLine
{
public:
	CCommandLine() = default;
	~CCommandLine() override = default;

	void Shutdown() override;
	const char* GetSystemName() const override { return COMMANDLINE_SYSTEM_VERSION; }

	void Create(const char* cmdline) override;
	void Create(int argc, char** argv) override;
	const char* Get() const override;

	bool HasParam(const char* param) const override;
	const char* GetParam(const char* param) const override;

private:
	static void Tokenize(const char* cmdline, std::vector<std::string>& tokens);
	virtual void ParseTokens(const std::vector<std::string>& tokens);

private:
	std::string m_CommandLine;
	std::map<std::string, std::string> m_Params;
};
