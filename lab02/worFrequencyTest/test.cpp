#include "pch.h"
#include "WordFrequency.cpp"

TEST(IsWord, empty_string) 
{
  EXPECT_TRUE(!IsWord(""));
}

TEST(IsWord, string_size_1)
{
	EXPECT_TRUE(!IsWord(" "));
}

TEST(IsWord, word_and_charcter_of_horizontal_tabulation)
{
	EXPECT_TRUE(!IsWord("word\t"));
}

TEST(IsWord, word_and_charcter_of_vertical_tabulation)
{
	EXPECT_TRUE(!IsWord("word\v"));
}

TEST(IsWord, word_and_charcter_of_carriage_return)
{
	EXPECT_TRUE(!IsWord("word\r"));
}

TEST(IsWord, word_and_charcter_of_line_feed)
{
	EXPECT_TRUE(!IsWord("word\n"));
}

TEST(IsWord, word_and_space_character)
{
	EXPECT_TRUE(!IsWord("word hello"));
}

TEST(IsWord, word_in_lower_case)
{
	EXPECT_TRUE(IsWord("word"));
}

TEST(IsWord, word_in_upper_case)
{
	EXPECT_TRUE(IsWord("WORD"));
}

TEST(IsWord, word_in_mixed_case)
{
	EXPECT_TRUE(IsWord("HeLLo"));
}

TEST(Tolower, transform_russian_word_from_lower_case_to_lower_case)
{
	ASSERT_EQ(ToLower("привет"), "привет");
}

TEST(Tolower, transform_russian_word_from_mixed_case_to_lower_case)
{
	ASSERT_EQ(ToLower("ПРивЕТ"), "привет");
}

TEST(Tolower, transform_russian_word_from_upper_case_to_lower_case)
{
	ASSERT_EQ(ToLower("МИР"), "мир");
}

TEST(Tolower, transform_english_word_from_lower_case_to_lower_case)
{
	ASSERT_EQ(ToLower("hello"), "hello");
}

TEST(Tolower, transform_english_word_from_mixed_case_to_lower_case)
{
	ASSERT_EQ(ToLower("HeLLo"), "hello");
}

TEST(Tolower, transform_english_word_from_upper_case_to_lower_case)
{
	ASSERT_EQ(ToLower("HELLO"), "hello");
}

TEST(CountFrequencyWords, count_word_frequency)
{
	std::stringstream inputStrm;
	std::stringstream outputStrm;

	inputStrm = std::stringstream();
	outputStrm = std::stringstream();

	inputStrm << "word\n" << "hello\n" << "book\n" << "BoOk\n"
		<< "WORD\n" << "Cat\n" << "Привет\n" << "МиР\n" << "мир\n";

	std::map<std::string, int> wordFrequency = CountFrequencyWords(inputStrm, outputStrm);
	std::map<std::string, int> checkWordFrequency = {
		{ "word", 2 },
		{ "hello", 1 },
		{ "book", 2 },
		{ "cat", 1 },
		{ "привет", 1},
		{ "мир", 2}
	};

	ASSERT_EQ(wordFrequency, checkWordFrequency);
}

TEST(PrintWordFrequncy, check_output)
{
	WordFrequency wordFrequency = {
		{ "book", 2 },
		{ "cat", 1 },
		{ "hello", 1 },
		{ "word", 2 },
		{ "привет", 1},
		{ "мир", 2}
	};

	std::stringstream outputStrm = std::stringstream();
	std::stringstream checkOutputStrm = std::stringstream();

	checkOutputStrm << "book->2\n" << "cat->1\n" 
		<< "hello->1\n" << "word->2\n" << "мир->2\n" << "привет->1\n";

	PrintWordFrequncy(outputStrm, wordFrequency);
	
	ASSERT_EQ(outputStrm.str(), checkOutputStrm.str());
}

int main(int argc, char **argv)
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}