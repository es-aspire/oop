#include "stdafx.h"
#include "WordFrequency.h"

bool IsWord(const std::string& word)
{
	if (word.empty())
	{
		return false;
	}

	const std::string WHITE_SPACE_CHARACTER = " \t\v\r\n\f";

	for (char ch : word)
	{
		if (WHITE_SPACE_CHARACTER.find(ch) != std::string::npos)
		{
			std::cout << "'" << ch << " " << static_cast<int>(WHITE_SPACE_CHARACTER.find(ch)) << "'";
			return false;
		}
	}

	return true;
}

std::string ToLower(const std::string& str)
{
	std::string result(str);

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] > 'A' && str[i] < 'Z')
		{
			result[i] += 'z' - 'Z';
		}
		if (str[i] > 'À' && str[i] < 'ß')
		{
			result[i] += 'ÿ' - 'ß';
		}
		if (str[i] == '¨') 
		{
			result[i] = '¸';
		}
	}

	return result;
}

WordFrequency CountFrequencyWords(std::istream& inputStrm, std::ostream& outputStrm)
{
	std::string commandLine;
	WordFrequency wordFrequency;

	outputStrm << "> ";

	while (std::getline(inputStrm, commandLine))
	{
		if (commandLine == "...")
		{
			break;
		}
		else if (IsWord(commandLine))
		{
			commandLine = ToLower(commandLine);
			++wordFrequency[commandLine];
		}
		else
		{
			outputStrm << commandLine << " it is not word\n"
					   << "A word is a sequence of one or more characters that are not spaces,\n"
					   << " tabs, and line-end characters.\n";
		}

		outputStrm << "> ";
	}

	return wordFrequency;
}

void PrintWordFrequncy(std::ostream& output, const WordFrequency& wordFrequency)
{
	for (const auto& item : wordFrequency)
	{
		output << item.first << "->" << item.second << "\n";
	}
}
