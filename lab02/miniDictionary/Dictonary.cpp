#include "stdafx.h"
#include "Dictonary.h"

bool IsEnglish(const std::string& word)
{
	constexpr char REGULAR_EXPRESSION[] = "^[a-zA-Z]([a-zA-Z -]+)[a-zA-Z]$";
	std::regex pattern(REGULAR_EXPRESSION, std::regex_constants::icase);
	std::smatch match;

	return (std::regex_match(word, match, pattern));
}

void PushWordToDictionary(DictionaryData& dictionaryData, const std::string& wordToTranslate, const std::string& translatedWord)
{
	std::string englishWord;
	std::string russianWord;

	if (IsEnglish(wordToTranslate))
	{
		englishWord = wordToTranslate;
		russianWord = translatedWord;
	}
	else
	{
		englishWord = translatedWord;
		russianWord = wordToTranslate;
	}

	dictionaryData.emplace(englishWord, russianWord);
}

bool ParseLine(const std::string& str, DictionaryData& dictionaryData)
{
	if (str.empty())
	{
		return true;
	}

	constexpr char REGULAR_EXPRESSION[] = "^([a-zA-Z -]+) : ([à-ÿÀ-ß¸¨ -]+)$";
	std::regex pattern(REGULAR_EXPRESSION, std::regex_constants::icase);
	std::smatch match;

	if (!std::regex_search(str, match, pattern))
	{
		return false;
	}

	dictionaryData.emplace(match[1], match[2]);

	return true;
}

std::string ToLower(const std::string& str)
{
	std::string result(str);

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			result[i] += 'z' - 'Z';
		}
		if (str[i] >= 'À' && str[i] <= 'ß')
		{
			result[i] += 'ÿ' - 'ß';
		}
		else if (str[i] == '¨')
		{
			result[i] = '¸';
		}
	}

	return result;
}

bool FindAllWord(const DictionaryData& dictionaryData, const std::string& wordToTranslate,
	std::string& translatedWord, bool isTranslateFromEnglishToRussian)
{
	bool wordTranslationWasFound = false;
	std::string findWord = ToLower(wordToTranslate);

	for (const auto& item : dictionaryData)
	{
		std::string currentWord = ToLower((isTranslateFromEnglishToRussian ? item.first : item.second));

		if (currentWord == findWord)
		{
			if (wordTranslationWasFound)
			{
				translatedWord += ", ";
			}

			translatedWord += isTranslateFromEnglishToRussian ? item.second : item.first;
			wordTranslationWasFound = true;
		}
	}

	return wordTranslationWasFound;
}

bool FoundAllWord(const DictionaryData& dictionaryData, const std::string& wordToTranslate, std::string& translatedWord)
{
	bool isTranslateFromEnglishToRussian = true;

	if (!FindAllWord(dictionaryData, wordToTranslate, translatedWord, isTranslateFromEnglishToRussian))
	{
		if (!FindAllWord(dictionaryData, wordToTranslate, translatedWord, !isTranslateFromEnglishToRussian))
		{
			return false;
		}
	}

	return true;
}

std::string Trim(const std::string& str)
{
	if (str.empty())
	{
		return "";
	}
	constexpr char BLANK_SYMBOL = ' ';
	size_t beginPos = str.find_first_not_of(BLANK_SYMBOL);
	if (beginPos == std::string::npos)
	{
		beginPos = 0;
	}
	size_t endPos = str.find_last_not_of(BLANK_SYMBOL);
	if (endPos == std::string::npos)
	{
		endPos = str.size() - 1;
	}
	std::string result = str.substr(beginPos, endPos - beginPos + 1);

	return result;
}

void AddWordToDictionary(std::istream& input, std::ostream& output,
	Dictionary& dictionary, const std::string& wordTranslate)
{
	std::string newWord = Trim(wordTranslate);
	output << "Unknown word “" << newWord << "”."
		   << " Enter the translations or empty string for failure.\n";

	std::string word;

	while (std::getline(input, word))
	{
		word = Trim(word);

		if (!word.empty())
		{
			dictionary.wasChange = true;
			
			PushWordToDictionary(dictionary.dictionaryData, newWord, word);
		}
		else
		{
			break;
		}
	}
}

bool ReadDictionary(std::istream& input, Dictionary& dictionary)
{
	std::string line;

	while (std::getline(input, line))
	{
		if (!ParseLine(line, dictionary.dictionaryData))
		{
			return false;
		}
	}

	return true;
}

bool Translate(Dictionary& dictionary, const std::string& wordToTranslate, std::string& translatedWord)
{
	std::string wordTranslate = Trim(wordToTranslate);

	return (FoundAllWord(dictionary.dictionaryData, wordTranslate, translatedWord));
}

void PrintDictionary(std::ostream& output, const Dictionary& dictionary)
{
	for (const auto& item : dictionary.dictionaryData)
	{
		output << item.first << " : " << item.second << "\n";
	}
}
