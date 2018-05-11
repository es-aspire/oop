#pragma once

using DictionaryData = std::unordered_multimap<std::string, std::string>;

struct Dictionary
{
	bool wasChange = false;
	std::string dictionaryFile;
	DictionaryData dictionaryData;
};

bool ReadDictionary(std::istream& input, Dictionary& dictionary);
bool Translate(Dictionary& dictionary, const std::string& wordToBeTranslate, std::string& translation);
void AddWordToDictionary(std::istream& input, std::ostream& output,
	Dictionary& dictionary, const std::string& wordTranslate);
void PrintDictionary(std::ostream& output, const Dictionary& dictionary);
