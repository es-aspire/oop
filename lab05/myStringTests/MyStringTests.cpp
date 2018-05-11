#include "stdafx.h"
#include "../MyString/MyString.cpp"

struct VerifyStringData
{
	VerifyStringData(std::string const& whenMsg,
		std::string const& thenMsg,
		size_t setStringLength,
		std::string const& setString,
		size_t expectedStringLength,
		std::string const& expectedString,
		bool isSuccess)
		: whenMsg(whenMsg)
		, thenMsg(thenMsg)
		, setStringLength(setStringLength)
		, setString(setString)
		, expectedStringLength(expectedStringLength)
		, expectedString(expectedString)
		, isSuccess(isSuccess)
	{
	}

	std::string whenMsg;
	std::string thenMsg;
	size_t setStringLength;
	std::string setString;
	size_t expectedStringLength;
	std::string expectedString;
	bool isSuccess;
};

using VerifyStrings = std::vector<VerifyStringData>;

class VerifyStringTest
{
public:
	static void VerifySetStringWithoutLength(const VerifyStrings& verifyStrings);
	static void VerifySetStringWithLength(const VerifyStrings& verifyStrings);
	static void VerifyStringDataTest(CMyString const& str, size_t length, std::string const& expectedStr, bool isSuccess);

private:
	static void VerifySetStringWithoutLength(VerifyStringData const& verifyStringData);
	static void VerifySetStringWithLength(VerifyStringData const& verifyStringData);
};

void VerifyStringTest::VerifySetStringWithoutLength(const VerifyStrings& verifyStrings)
{
	for (const auto& verifyStringData : verifyStrings)
	{
		VerifySetStringWithoutLength(verifyStringData);
	}
}

void VerifyStringTest::VerifySetStringWithLength(const VerifyStrings& verifyStrings)
{
	for (const auto& verifyStringData : verifyStrings)
	{
		VerifySetStringWithLength(verifyStringData);
	}
}

void VerifyStringTest::VerifyStringDataTest(CMyString const& str, size_t length, std::string const& expectedStr, bool isSuccess)
{
	REQUIRE(str.GetLength() == length);
	REQUIRE((std::string(str.GetStringData()) == expectedStr) == isSuccess);
}

void VerifyStringTest::VerifySetStringWithoutLength(VerifyStringData const& verifyStringData)
{
	AND_WHEN(verifyStringData.whenMsg)
	{
		CMyString str(verifyStringData.setString.c_str());

		THEN(verifyStringData.thenMsg.c_str())
		{
			VerifyStringDataTest(str, verifyStringData.expectedStringLength, verifyStringData.expectedString, verifyStringData.isSuccess);
		}
	}
}

void VerifyStringTest::VerifySetStringWithLength(VerifyStringData const& verifyStringData)
{
	AND_WHEN(verifyStringData.whenMsg)
	{
		CMyString str(verifyStringData.setString.c_str(), verifyStringData.setStringLength);

		THEN(verifyStringData.thenMsg.c_str())
		{
			VerifyStringDataTest(str, verifyStringData.expectedStringLength, verifyStringData.expectedString, verifyStringData.isSuccess);
		}
	}
}

struct VerifySubstringData
{
	VerifySubstringData(std::string const& whenMsg,
		std::string const& thenMsg,
		size_t start,
		size_t length,
		std::string const& expectedString)
		: whenMsg(whenMsg)
		, thenMsg(thenMsg)
		, start(start)
		, length(length)
		, expectedString(expectedString)
	{
	}

	std::string whenMsg;
	std::string thenMsg;
	size_t start;
	size_t length;
	std::string expectedString;
};

using VerifySubstrings = std::vector<VerifySubstringData>;

void TestSubstring(CMyString const& inputString, VerifySubstringData const& verifySubstringData)
{
	REQUIRE(inputString.SubString(verifySubstringData.start, verifySubstringData.length) == verifySubstringData.expectedString);
}

void VerifySubstring(CMyString const& str, VerifySubstringData const& verifySubstringData)
{
	WHEN(verifySubstringData.whenMsg)
	{
		THEN(verifySubstringData.thenMsg)
		{
			TestSubstring(str, verifySubstringData);
		}
	}
}

void VerifySubstringDataTest(std::string const& setString, VerifySubstrings const& verifySubstrings)
{
	CMyString str(setString);

	for (const auto& verifySubstringData : verifySubstrings)
	{
		VerifySubstring(str, verifySubstringData);
	}
}

enum Operation
{
	EQUAL,
	NOT_EQUAL,
	MORE,
	MORE_OR_EQUAL,
	LESS,
	LESS_OR_EQUAL,
	UNKOWN
};

struct VerifyStringComparationOperatorData
{
	VerifyStringComparationOperatorData(std::string const& whenMsg,
		std::string const& thenMsg,
		std::string const& lhs,
		std::string const& rhs,
		Operation operation,
		bool isSuccess)
		: whenMsg(whenMsg)
		, thenMsg(thenMsg)
		, lhs(lhs)
		, rhs(rhs)
		, operation(operation)
		, isSuccess(isSuccess)
	{
	}

	std::string whenMsg;
	std::string thenMsg;
	std::string lhs;
	std::string rhs;
	Operation operation;
	bool isSuccess;
};

using StringOperationMap = std::map<Operation, std::function<bool(CMyString const& lhs, CMyString const& rhs)>>;

static const StringOperationMap OPERATION_MAP = {
	std::make_pair(Operation::EQUAL, [](CMyString const& lhs, CMyString const& rhs) {
		return (lhs == rhs);
	}),
	std::make_pair(Operation::NOT_EQUAL, [](CMyString const& lhs, CMyString const& rhs) {
		return (lhs != rhs);
	}),
	std::make_pair(Operation::MORE, [](CMyString const& lhs, CMyString const& rhs) {
		return lhs < rhs;
	}),
	std::make_pair(Operation::LESS_OR_EQUAL, [](CMyString const& lhs, CMyString const& rhs) {
		return (lhs >= rhs);
	}),
	std::make_pair(Operation::LESS, [](CMyString const& lhs, CMyString const& rhs) {
		return (lhs > rhs);
	}),
	std::make_pair(Operation::MORE_OR_EQUAL, [](CMyString const& lhs, CMyString const& rhs) {
		return lhs <= rhs;
	})
};

bool VerifyOperation(VerifyStringComparationOperatorData const& verifyOperation)
{
	auto it = OPERATION_MAP.find(verifyOperation.operation);
	if (it == OPERATION_MAP.end())
	{
		throw std::logic_error("unkown operation");
	}

	CMyString lhs(verifyOperation.lhs);
	CMyString rhs(verifyOperation.rhs);

	return it->second(lhs, rhs);
}

using OperationToStringData = std::map<Operation, std::string>;

static const OperationToStringData OPERATION_TO_STRING = {
	std::make_pair(Operation::EQUAL, "=="),
	std::make_pair(Operation::EQUAL, "!="),
	std::make_pair(Operation::MORE, "<"),
	std::make_pair(Operation::MORE_OR_EQUAL, "<="),
	std::make_pair(Operation::LESS, ">"),
	std::make_pair(Operation::LESS_OR_EQUAL, ">="),
};

std::string OperationToString(Operation operation)
{
	auto it = OPERATION_TO_STRING.find(operation);

	if (it == OPERATION_TO_STRING.end())
	{
		return std::string();
	}

	return it->second;
}

void VerifyOperatorData(VerifyStringComparationOperatorData const& verifyData)
{
	WHEN(verifyData.whenMsg)
	{
		THEN(verifyData.thenMsg)
		{
			try
			{
				REQUIRE(VerifyOperation(verifyData) == verifyData.isSuccess);
			}
			catch (std::exception const& err)
			{
				std::cerr << err.what() << std::endl;

				REQUIRE(false);
			}
		}
	}
}

using VerifyOperationsData = std::vector<VerifyStringComparationOperatorData>;

void VerifyOperation(VerifyOperationsData const& verifyOperationsData)
{
	for (const auto& operationData : verifyOperationsData)
	{
		VerifyOperatorData(operationData);
	}
}

using VerifyOperations = std::map<Operation, VerifyOperationsData>;

void CheckOperators(VerifyOperations const& verifyOperations)
{
	for (const auto& item : verifyOperations)
	{
		THEN("verify operator '" + OperationToString(item.first) + "'")
		{
			VerifyOperation(item.second);
		}
	}
}

TEST_CASE("MyStringTests")
{
	GIVEN("Initially")
	{
		WHEN("initialize without parameter")
		{
			CMyString str;

			THEN("length is equal 0 and string is empty")
			{
				VerifyStringTest::VerifyStringDataTest(str, 0, "\0", true);
			}
		}

		WHEN("construct the string data string without specifying length")
		{
			VerifyStrings verifyStringsWithoutLength = {
				VerifyStringData("empty string",
					"length is equal 1 and string is empty",
					std::numeric_limits<size_t>::quiet_NaN(), "", 0, "\0", true),

				VerifyStringData("string contains one character",
					"length is equal 2 and string should contains initialize character",
					std::numeric_limits<size_t>::quiet_NaN(), "q", 1, "q", true),

				VerifyStringData("string contains more than one character without null character",
					"length is equal a size of input string and string should contains initialize character",
					std::numeric_limits<size_t>::quiet_NaN(), "hello world", 11, "hello world", true),

				VerifyStringData("string contains more than one character with null character",
					"length of the string is equal to the substring before end-of-line character and string should contains initialize character before a null character",
					std::numeric_limits<size_t>::quiet_NaN(), "hello \0world", 6, "hello \0", true)
			};

			VerifyStringTest::VerifySetStringWithoutLength(verifyStringsWithoutLength);
		}

		WHEN("construct the string data string with specifying length")
		{
			VerifyStrings verifyStringsWithLength = {
				VerifyStringData("empty string",
					"length is equal 1 and string is empty",
					0, "", 0, "\0", true),

				VerifyStringData("string contains only null character",
					"length is equal 1 and string should contains only null character",
					0, "\0", 0, "\0", true),

				VerifyStringData("string contains more than one character without null character",
					"length is equal 2 and string should contains initialize character and null character",
					1, "w", 1, "w\0", true),

				VerifyStringData("string contains more than one character with null character in center of string",
					"length is equal 2 and string should contains initialize character",
					12, "hello \0world", 12, "hello \0world\0", true),
			};

			VerifyStringTest::VerifySetStringWithLength(verifyStringsWithLength);
		}

		WHEN("string is constructed by copying other CMyString")
		{
			CMyString stringToCopy("qwerty");
			CMyString resultString(stringToCopy);

			THEN("data of the strings should be coincide")
			{
			}
		}

		WHEN("get substring")
		{
			AND_WHEN("source string is empty")
			{
				VerifySubstrings verifySubstrings = {
					VerifySubstringData("get substring with length is equal 0 and starting from 0 position",
						"returns an empty substring",
						0, 0, ""),
					VerifySubstringData("get substring with length is more 0 and starting from 0 position",
						"returns an empty substring",
						1, 0, ""),
					VerifySubstringData("get substring with length is equal 0 and starting from 1 position",
						"returns an empty substring",
						0, 1, "")
				};

				VerifySubstringDataTest("", verifySubstrings);
			}

			AND_WHEN("source string length is not zero")
			{
				std::string setString("hello world");

				VerifySubstrings verifySubstrings = {
					VerifySubstringData("starting position is more than string length",
						"returns an empty substring",
						20, 4, ""),
					VerifySubstringData("starting position + substring length is more than string length",
						"returns a substring from the starting position to the end of the line",
						8, 1000, "rld"),
					VerifySubstringData("starting position + substring length is less than string length",
						"substring of substring length and starting from start position",
						8, 3, "rld"),
				};

				VerifySubstringDataTest(setString, verifySubstrings);
			}
		}

		THEN("allow clear string")
		{
			CMyString str("hello world");

			WHEN("clear string")
			{
				str.Clear();

				THEN("string length is equal to 0 and data is empty")
				{
					VerifyStringTest::VerifyStringDataTest(str, 0, "", true);
				}
			}
		}

		WHEN("concatenation to string")
		{
			THEN("allow concatenate CMyString with CMyString")
			{
				CMyString str1("123");
				CMyString str2("456");
				std::stringstream strm;

				strm << (str1 + str2);

				REQUIRE(strm.str() == std::string("123456"));
			}

			THEN("allow concatenate std::string with CMyString")
			{
				std::string str1("123");
				CMyString str2("456");
				std::stringstream strm;

				strm << (str1 + str2);

				REQUIRE(strm.str() == std::string("123456"));
			}

			THEN("allow concatenate std::string with CMyString")
			{
				const char* str1 = "123";
				CMyString str2("456");
				std::stringstream strm;

				strm << (str1 + str2);

				REQUIRE(strm.str() == std::string("123456"));
			}

			THEN("allow concatenating CMyString with CMyString with Assignment")
			{
				CMyString str1("123");
				CMyString str2("456");
				std::stringstream strm;

				str1 += str2;
				REQUIRE(str1 == "123456");
			}
		}

		WHEN("assigning some string")
		{
			THEN("allow assigning char*")
			{
				CMyString str;

				str = "12345";

				VerifyStringTest::VerifyStringDataTest(str, 5, "12345", true);
			}

			THEN("allow assigning std::string")
			{
				std::string stdString("hello world");
				CMyString str;

				str = stdString;

				VerifyStringTest::VerifyStringDataTest(str, stdString.size(), stdString, true);
			}

			THEN("allow assigning CMyString")
			{
				CMyString myString("hello world");
				CMyString str;

				str = myString;

				VerifyStringTest::VerifyStringDataTest(str, myString.GetLength(), "hello world", true);
			}

			THEN("allows you to assign yourself string")
			{
				CMyString myString("hello world");
				CMyString str;

				str = myString;

				VerifyStringTest::VerifyStringDataTest(str, myString.GetLength(), "hello world", true);
			}
		}

		WHEN("check operator of square brackets")
		{
			THEN("exist indexed access to string characters by an integer index for reading")
			{
				const CMyString STR("hello world");
				std::stringstream strm;

				for (size_t i = 0; i < STR.GetLength(); ++i)
				{
					strm << STR[i];
				}

				REQUIRE(strm.str() == std::string("hello world"));
			}

			THEN("exist indexed access to string characters by an integer index for writing")
			{
				CMyString str("hello world");

				for (size_t i = 0; i < str.GetLength(); ++i)
				{
					str[i] = '#';
				}

				REQUIRE(str == std::string("###########"));
			}
		}

		WHEN("Symbolic comparison of the contents of two lines")
		{
			VerifyOperationsData verifyEqual = {
				VerifyStringComparationOperatorData("two strings length is not equal",
					"operator return false",
					"123", "1234567", Operation::EQUAL, false),
				VerifyStringComparationOperatorData("two strings length is equal",
					"operator return true",
					"123", "123", Operation::EQUAL, true),
			};

			VerifyOperationsData verifyNotEqual = {
				VerifyStringComparationOperatorData("two strings length is not equal",
					"operator return true",
					"123", "1234567", Operation::NOT_EQUAL, true),
				VerifyStringComparationOperatorData("two strings length is equal",
					"operator return false",
					"123", "123", Operation::NOT_EQUAL, false),
			};

			VerifyOperationsData verifyMore = {
				VerifyStringComparationOperatorData("left string < right string",
					"operator return true",
					"123", "1234567", Operation::MORE, true),
				VerifyStringComparationOperatorData("two strings length is equal",
					"operator return false",
					"123", "123", Operation::MORE, false),
				VerifyStringComparationOperatorData("left string > right string",
					"operator return false",
					"123123", "123", Operation::MORE, false)
			};

			VerifyOperationsData verifyMoreOrEqual = {
				VerifyStringComparationOperatorData("left string <= right string",
					"operator return true",
					"123", "1234567", Operation::MORE_OR_EQUAL, true),
				VerifyStringComparationOperatorData("two strings length is equal",
					"operator return false",
					"123", "123", Operation::MORE_OR_EQUAL, true),
				VerifyStringComparationOperatorData("left string <= right string",
					"operator return false",
					"123123", "123", Operation::MORE_OR_EQUAL, false)
			};

			VerifyOperationsData verifyLess = {
				VerifyStringComparationOperatorData("left string > right string",
					"operator return true",
					"1234567", "123", Operation::LESS, true),
				VerifyStringComparationOperatorData("two strings length is equal",
					"operator return false",
					"123", "123", Operation::LESS, false),
				VerifyStringComparationOperatorData("left string > right string",
					"operator return false",
					"123", "1234567", Operation::LESS, true)
			};

			VerifyOperationsData verifyLessOrEqual = {
				VerifyStringComparationOperatorData("left string >= right string",
					"operator return true",
					"1234567", "123", Operation::LESS_OR_EQUAL, true),
				VerifyStringComparationOperatorData("two strings length is equal",
					"operator return true",
					"123", "123", Operation::LESS_OR_EQUAL, true),
				VerifyStringComparationOperatorData("left string >= right string",
					"operator return false",
					"123", "1234567", Operation::LESS_OR_EQUAL, false)
			};

			VerifyOperations veritfyOperations = {
				std::make_pair(Operation::EQUAL, verifyEqual),
				std::make_pair(Operation::NOT_EQUAL, verifyNotEqual),
				std::make_pair(Operation::MORE, verifyMore),
				std::make_pair(Operation::MORE_OR_EQUAL, verifyMoreOrEqual),
				std::make_pair(Operation::LESS, verifyLess),
				std::make_pair(Operation::LESS_OR_EQUAL, verifyLessOrEqual)
			};

			CheckOperators(veritfyOperations);
		}

		THEN("verify the output operator")
		{
			CMyString str("12345\n1234");

			std::stringstream strm;

			strm << str;

			REQUIRE(strm.str() == std::string("12345\n1234"));
		}

		WHEN("verify the input operator")
		{
			CMyString str;

			THEN("read before null character")
			{
				std::stringstream strm("123435 \0hello world \n");

				strm >> str;

				REQUIRE(str == std::string("123435"));
			}
		}
	}
}

TEST_CASE("Test iterator")
{
	CMyString str("Hello world");

	SECTION("allows to get an iterator that points to the start character")
	{
		auto it = str.begin();

		REQUIRE(*it == 'H');
	}

	SECTION("allows to pass a non-constant string in the forward direction")
	{
		CMyString str("Hello world");

		std::stringstream strm;

		for (auto it = str.begin(); it != str.end(); ++it)
		{
			strm << *it;
		}

		REQUIRE(strm.str() == str);
	}

	SECTION("allows to pass a constant string in the forward direction")
	{
		const CMyString str("Hello world");
		std::stringstream strm;

		for (auto it = str.cbegin(); it != str.cend(); ++it)
		{
			strm << *it;
		}

		REQUIRE(strm.str() == str);
	}

	SECTION("allows to pass a non-constant string in the backword direction")
	{
		CMyString str("Hello world");

		std::stringstream strm;

		for (auto it = str.rbegin(); it != str.rend(); ++it)
		{
			strm << *it;
		}

		REQUIRE(strm.str() == "dlrow olleH");
	}

	SECTION("allows to pass a constant string in the backword direction")
	{
		CMyString str("Hello world");

		std::stringstream strm;

		for (auto it = str.crbegin(); it != str.crend(); ++it)
		{
			strm << *it;
		}

		REQUIRE(strm.str() == "dlrow olleH");
	}

	SECTION("support for iterating over elements using the range-based version of the for statement")
	{
		CMyString strRangeBase("Hello world");

		std::stringstream strm;

		for (auto ch : strRangeBase)
		{
			strm << ch;
		}

		REQUIRE(strm.str() == str);
	}

	SECTION("allow to indexed access to the elements of the string relative to the iterator using the [] operator")
	{
		CMyString str("hello world");
		auto it = str.begin();

		std::stringstream strm;

		strm << it[2] << it[4] << it[8] << it[10];

		REQUIRE(strm.str() == "lord");
	}
}

TEST_CASE("test stl algorithm wiht CMyString")
{
	CMyString myStr("123456");
	std::string stdStr("123456");

	SECTION("std::all_of")
	{
		bool resultMyStr = std::all_of(myStr.begin(), myStr.end(), [](char ch) {
			return isdigit(ch);
		});
			
		bool resultStdStr = std::all_of(stdStr.begin(), stdStr.end(), [](char ch) {
			return isdigit(ch);
		});

		REQUIRE(resultMyStr == resultStdStr);
	}

	SECTION("std::any_of")
	{
		bool resultMyStr = std::any_of(myStr.begin(), myStr.end(), [](char ch) {
			return isdigit(ch);
		});
			
		bool resultStdStr = std::any_of(stdStr.begin(), stdStr.end(), [](char ch) {
			return isdigit(ch);
		});

		REQUIRE(resultMyStr == resultStdStr);
	}
	
	SECTION("std::none_of")
	{
		bool resultMyStr = std::none_of(myStr.begin(), myStr.end(), [](char ch) {
			return isdigit(ch);
		});
			
		bool resultStdStr = std::none_of(stdStr.begin(), stdStr.end(), [](char ch) {
			return isdigit(ch);
		});

		REQUIRE(resultMyStr == resultStdStr);
	}

	SECTION("std::distance")
	{
		auto resultMyStr = std::distance(myStr.begin(), myStr.end());
		auto resultStdStr = std::distance(stdStr.begin(), stdStr.end());

		REQUIRE(resultMyStr == resultStdStr);
	}
}
