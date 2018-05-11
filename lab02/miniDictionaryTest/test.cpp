#include "pch.h"
#include "../miniDictionary/Dictonary.cpp"

bool CompareMap(DictionaryData const& lhs, DictionaryData const& rhs)
{
	return lhs.size() == rhs.size()
		&& std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

void PushWordToDictionaryTest(const std::string& wordToBeTranslate, const std::string& translation)
{
	DictionaryData dictionaryData;

	PushWordToDictionary(dictionaryData, wordToBeTranslate, translation);

	DictionaryData checkDictionaryData;
	if (IsEnglish(wordToBeTranslate))
	{
		checkDictionaryData.insert(std::pair<std::string, std::string>(wordToBeTranslate, translation));
	}
	else
	{
		checkDictionaryData.insert(std::pair<std::string, std::string>(translation, wordToBeTranslate));
	}

	EXPECT_TRUE(CompareMap(dictionaryData, checkDictionaryData));
}

void ParseLineTest(const std::string& englishWord, const std::string& delimeter,
	const std::string& russianWord, bool expectedResult)
{
	std::string str = englishWord + delimeter + russianWord;
	DictionaryData dictionaryData;

	EXPECT_EQ(ParseLine(str, dictionaryData), expectedResult);

	if (expectedResult)
	{
		DictionaryData checkDictionaryData;

		checkDictionaryData.insert(std::pair<std::string, std::string>(englishWord, russianWord));
		EXPECT_TRUE(CompareMap(dictionaryData, checkDictionaryData));
	}
}

void ToLowerTest(const std::string& str, const std::string& checkStr)
{
	EXPECT_TRUE(ToLower(str) == checkStr);
}

void FindAllWordTest(std::vector<std::pair<std::string, std::string>>& vect,
	const std::string& wordToBeTranslated, const std::string& checkTranslation, bool fromEnglishToRussian)
{
	DictionaryData dictionaryData;

	for (const auto& item : vect)
	{
		PushWordToDictionary(dictionaryData, item.first, item.second);
	}

	std::string translation;

	EXPECT_TRUE(FindAllWord(dictionaryData, wordToBeTranslated, translation, fromEnglishToRussian));

	EXPECT_TRUE(translation == checkTranslation);
}

TEST(IsEnglishTest, unresolved_symbol_in_english_expression)
{
	EXPECT_TRUE(!IsEnglish("2345"));
}

TEST(IsEnglishTest, not_an_english_expression_or_word)
{
	EXPECT_TRUE(!IsEnglish("привет мир"));
}

TEST(IsEnglishTest, one_english_word)
{
	EXPECT_TRUE(IsEnglish("hello"));
}

TEST(IsEnglishTest, two_english_word)
{
	EXPECT_TRUE(IsEnglish("hello world"));
}

TEST(IsEnglishTest, hyphen_at_the_begin_of_the_word)
{
	EXPECT_TRUE(!IsEnglish("-hello world"));
}

TEST(IsEnglishTest, correct_english_word_with_a_hyphen)
{
	EXPECT_TRUE(IsEnglish("camera-ready"));
}

TEST(IsEnglishTest, hyphen_at_the_end_of_the_word)
{
	EXPECT_TRUE(!IsEnglish("hello world-"));
}

TEST(PushWordToDictionaryTest, push_english_and_russian_words)
{
	PushWordToDictionaryTest("car", "машина");
}

TEST(PushWordToDictionaryTest, push_russian_and_english_words)
{
	PushWordToDictionaryTest("машина", "car");
}

TEST(ParseLineTest, invalid_english_word)
{
	ParseLineTest("123", " : ", "мир", false);
}

TEST(ParseLineTest, invalid_delimiter)
{
	ParseLineTest("world", " -> ", "мир", false);
}

TEST(ParseLineTest, invalid_russian_word)
{
	ParseLineTest("world", " -> ", "234", false);
}

TEST(ParseLineTest, all_parts_of_line_is_a_valid)
{
	ParseLineTest("car", " : ", "машина", true);
}

TEST(StringToLowerTest, russian_upper_case)
{
	ToLowerTest("КОТ", "кот");
}

TEST(StringToLowerTest, russian_mixed_case)
{
	ToLowerTest("КоТ", "кот");
}

TEST(StringToLowerTest, russian_lower_case)
{
	ToLowerTest("кот", "кот");
}

TEST(StringToLowerTest, english_upper_case)
{
	ToLowerTest("CAT", "cat");
}

TEST(StringToLowerTest, english_mixed_case)
{
	ToLowerTest("CaT", "cat");
}

TEST(StringToLowerTest, english_lower_case)
{
	ToLowerTest("cat", "cat");
}

TEST(TrimTest, empty_str)
{
	std::string str = Trim("");
	EXPECT_EQ(str, "");
}

TEST(TrimTest, spaces_at_the_beginning_and_at_the_end)
{
	std::string str = Trim("   hello world    ");
	EXPECT_EQ(str, "hello world");
}

TEST(FindAllEnglishWordTest, find_all_translation_of_the_english_word_in_a_upper_case)
{
	std::vector<std::pair<std::string, std::string>> vect = { std::make_pair("car", "машина"),
		std::make_pair("car", "автомобиль"),
		std::make_pair("car", "вагонетка") };

	FindAllWordTest(vect, "CAR", "машина, автомобиль, вагонетка", true);
}

TEST(FindAllEnglishWordTest, find_all_translation_of_the_english_word_in_a_mixed_case)
{
	std::vector<std::pair<std::string, std::string>> vect = { std::make_pair("car", "машина"),
		std::make_pair("car", "автомобиль"),
		std::make_pair("car", "вагонетка") };

	FindAllWordTest(vect, "cAr", "машина, автомобиль, вагонетка", true);
}

TEST(FindAllEnglishWordTest, find_all_translation_of_the_english_word_in_a_lower_case)
{
	std::vector<std::pair<std::string, std::string>> vect = {
		std::make_pair("car", "машина"),
		std::make_pair("car", "автомобиль"),
		std::make_pair("car", "вагонетка")
	};

	FindAllWordTest(vect, "car", "машина, автомобиль, вагонетка", true);
}

TEST(FindAllRussianWordTest, find_all_translation_of_the_russian_word_in_a_upper_case)
{
	std::vector<std::pair<std::string, std::string>> vect = {
		std::make_pair("speech", "речь"),
		std::make_pair("talk", "речь"),
		std::make_pair("words", "речь")
	};

	FindAllWordTest(vect, "РЕЧЬ", "talk, speech, words", false);
}

TEST(FindAllRussianWordTest, find_all_translation_of_the_russian_word_in_a_mixed_case)
{
	std::vector<std::pair<std::string, std::string>> vect = {
		std::make_pair("speech", "речь"),
		std::make_pair("talk", "речь"),
		std::make_pair("words", "речь")
	};

	FindAllWordTest(vect, "Речь", "talk, speech, words", false);
}

TEST(FindAllRussianWordTest, find_all_translation_of_the_russian_word_in_a_lower_case)
{
	std::vector<std::pair<std::string, std::string>> vect = {
		std::make_pair("speech", "речь"),
		std::make_pair("talk", "речь"),
		std::make_pair("words", "речь")
	};

	FindAllWordTest(vect, "речь", "talk, speech, words", false);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
