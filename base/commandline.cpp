#include "base/icommandline.h"
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>


class CCommandLine : public ICommandLine
{
public:
	CCommandLine();
	~CCommandLine();

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
ICommandLine* CommandLine()
{
	return &g_CommandLine;
}

CCommandLine::CCommandLine()
{

}

CCommandLine::~CCommandLine()
{

}

/**
 * \brief Parses the command line from a string.
 * \param cmdline The input command line string.
 */
void CCommandLine::Create(const char* cmdline)
{
	std::vector<std::string> tokens;
	m_sCommandLine = cmdline;
	Tokenize(cmdline, tokens);
	ParseTokens(tokens);
}

/**
 * \brief Initializes the parser from command line arguments.
 * \param argc 
 * \param argv 
 */
void CCommandLine::Create(int argc, char** argv)
{
	std::string cmdline;
	for (int i = 1; i < argc; ++i)	// We want to skip the first argument passed
	{
		cmdline += std::string(argv[i]) + " ";
	}
	Create(cmdline.c_str());
}

/**
 * \brief Gets the original command line string.
 * \return Original command line string, or NULL if not initialized.
 */
const char* CCommandLine::Get() const
{
	return m_sCommandLine.c_str();
}

/**
 * \brief Checks if a parameter exists.
 * \param param String name of the parameter.
 * \return true if the parameter is present, or false if not.
 */
bool CCommandLine::HasParam(const char* param) const
{
	return m_mapParams.find(param) != m_mapParams.end();
}

/**
 * \brief Gets parameter value.
 * \param param String name of the parameter.
 * \return String value specified after the parameter, or NULL if no value is present.
 */
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
