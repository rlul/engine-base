#include "core/icommandline.h"
#include "subsystem.h"
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>


class CCommandLine : public ICommandLine
{
public:
	CCommandLine() = default;
	~CCommandLine() override = default;

	void Shutdown() override;
	const char* GetSystemName() const override { return COMMANDLINE_SYSTEM_VERSION; };

	void Create(const char* cmdline) override;
	void Create(int argc, char** argv) override;
	const char* Get() const override;

	bool HasParam(const char* param) const override;
	const char* GetParam(const char* param) const override;

private:
	static void Tokenize(const char* cmdline, std::vector<std::string>& tokens);
	void ParseTokens(const std::vector<std::string>& tokens);

private:
	std::string m_sCommandLine;
	std::map<std::string, std::string> m_mapParams;
};

CCommandLine g_CommandLine;
CREATE_SINGLE_SYSTEM( CCommandLine, ICommandLine, COMMANDLINE_SYSTEM_VERSION, g_CommandLine );

void CCommandLine::Shutdown()
{
	m_sCommandLine.clear();
	m_mapParams.clear();
}

void CCommandLine::Create(const char* cmdline)
{
	std::vector<std::string> tokens;
	m_sCommandLine = cmdline;
	Tokenize(cmdline, tokens);
	ParseTokens(tokens);
}

void CCommandLine::Create(int argc, char** argv)
{
	std::string cmdline;
	for (int i = 1; i < argc; ++i)	// We want to skip the first argument passed
	{
		cmdline += std::string(argv[i]) + " ";
	}
	Create(cmdline.c_str());
}

const char* CCommandLine::Get() const
{
	return m_sCommandLine.c_str();
}

bool CCommandLine::HasParam(const char* param) const
{
	return m_mapParams.contains(param);
}

const char* CCommandLine::GetParam(const char* param) const
{
	auto it = m_mapParams.find(param);
	return (it != m_mapParams.end()) ? it->second.c_str() : NULL;
}

void CCommandLine::Tokenize(const char* cmdline, std::vector<std::string>& tokens)
{
	std::string input_string(cmdline);
	std::istringstream iss(input_string);
	std::string token;

	while (iss >> std::quoted(token, '\"'))
	{
		tokens.push_back(token);
	}
}

void CCommandLine::ParseTokens(const std::vector<std::string>& tokens)
{
	size_t tokens_count = tokens.size();

	for (size_t i = 0; i < tokens_count; ++i)
	{
		const std::string& current_token = tokens[i];

		// Skip tokens that don't start with '-'
		if (!current_token.empty() && current_token[0] != '-') {
			continue;
		}

		std::string key;
		std::string value;

		// If the token starts with '-', exclude the first character
		if (!current_token.empty() && current_token[0] == '-')
		{
			if (current_token.size() > 1)
			{
				key = current_token.substr(1);
			}
			else
			{
				// If the token consists only of '-', skip it
				continue;
			}

			// Check that we have the next token and it doesn't start with '-'
			if (i + 1 < tokens_count && tokens[i + 1][0] != '-')
			{
				// Use the next token as the value for the current key
				value = tokens[i + 1];
				++i;  // Skip the next token
			}
		}

		// Set the value for the current key
		m_mapParams[key] = value;
	}
}
