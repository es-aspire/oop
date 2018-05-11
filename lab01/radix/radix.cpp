// radix.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

static const unsigned VALID_ARGUMENT_COUNT = 4;
static const unsigned MIN_NOTATION = 2;
static const unsigned MAX_NOTATION = 36;
static const unsigned BASE_RADIX = 10;
static const string DIGITS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char SYMBOL_MINUS = '-';

int StringToInt(const string &str, int radix, bool &wasError);
bool IsValidRadix(int radix);
bool IsValidDigitOnStr(char ch, int radix);
bool IsValidValue(const string &valueStr, int radix);
bool ParseCommandLine(int argc, char* argv[], int &srcNotation, int &dstNotation, string& srcValue);

int CharToDigit(char ch);
char DigitToChar(int digit);
int ConvertToDecimal(const string &valueStr, int radix, bool &wasError);
string Radix(int srcNotation, int dstNotation, const string &srcValue, bool &wasError);
bool Radix(int srcNotation, int dstNotation, const string &srcValue);

bool Overflow(int a, int b, bool isPositive)
{
	if (isPositive)
	{
		return a > (INT_MAX / b);
	}
	else
	{
		return b < (INT_MIN / a);
	}
}

int main(int argc, char* argv[])
{
	int a = 2;
	int b = 1073741824;
	bool isPositive = false;
	cout << ((-1) * INT_MIN) << "\n";
	if (Overflow(a, b, isPositive))
	{
		cout << "overflow " << "\n";
	}
	else
	{
		cout << "not overflow " << "\n";
	}
	//cout << Overflow(a, b, isPositive) << "\n";
	int srcNotation = 0;
	int dstNotation = 0;
	string srcValue;
	if (!ParseCommandLine(argc, argv, srcNotation, dstNotation, srcValue))
	{
		return 1;
	}
	/*bool success = Radix(srcNotation, dstNotation, srcValue);
	if (!success) 
	{
		return 1;
	}*/
	return 0;
}

int StringToInt(const string &str, int radix, bool &wasError)
{
	int result = 0;
	try
	{
		size_t *pos = 0;
		result = stoi(str, pos, radix);
	}
	catch (const invalid_argument &e)
	{
		wasError = true;
		cerr << e.what() << "\n";
	}
	catch (const out_of_range &e)
	{
		wasError = true;
		cerr << e.what() << "\n";
	}
	return result;
}

bool IsValidRadix(int radix)
{
	return MIN_NOTATION <= radix && radix <= MAX_NOTATION;
}

bool IsValidDigitOnStr(char ch, int radix)
{
	return (DIGITS[0] <= ch && ch <= DIGITS[radix - 1]);
}

bool IsValidValue(const string &valueStr, int radix)
{
	size_t i = 0;
	if (valueStr[0] == SYMBOL_MINUS)
	{
		i++;
	}
	for (; i < valueStr.size(); ++i)
	{
		if (!IsValidDigitOnStr(valueStr[i], radix))
		{
			return false;
		}
	}
	return true;
}

bool ParseCommandLine(int argc, char* argv[], int &srcNotation, int &dstNotation, string& srcValue)
{
	if (argc != VALID_ARGUMENT_COUNT)
	{
		cout << "Invalid argument count\nUsage: radix.exe <source notation> <destination notation> <value>\n";
		return false;
	}
	string srcNotationStr = argv[1];
	bool wasError = false;
	srcNotation = StringToInt(srcNotationStr, BASE_RADIX, wasError);
	if (wasError)
	{
		return false;
	}
	if (!IsValidRadix(srcNotation))
	{
		cout << "The radix \"" << srcNotation << "\" not included in the valid range. ["
			<< MIN_NOTATION << ", " << MAX_NOTATION << "]\n";
		return false;
	}
	string dstNotationStr = argv[2];
	dstNotation = StringToInt(dstNotationStr, BASE_RADIX, wasError);
	if (wasError)
	{
		return false;
	}
	srcValue = argv[3];
	if (!IsValidRadix(dstNotation))
	{
		cout << "The radix \"" << dstNotation
			<< "\" not included in the valid range. ["
			<< MIN_NOTATION << ", " << MAX_NOTATION << "]\n";
		return false;
	}
	if (srcValue.empty())
	{
		cout << "<value> can't be empty.\n";
		return false;
	}
	if (!IsValidValue(srcValue, srcNotation))
	{
		cout << " The " << srcNotation << "th does not include " << srcValue << "\n";
		return false;
	}
	return true;
}

int CharToDigit(char ch)
{
	if (DIGITS[0] <= ch && ch <= DIGITS[9])
	{
		return (ch - '0');
	}
	if (DIGITS[10] <= ch && ch <= DIGITS[DIGITS.size() - 1])
	{
		return (ch - 'A' + 10);
	}
	return DIGITS[0];
}

char DigitToChar(int digit)
{
	if (0 <= digit && digit <= 9)
	{
		return ('0' + digit);
	}
	if (10 <= digit && digit <= 36)
	{
		return ('A' + digit - 10);
	}
	return '0';
}

bool Overflow(int a, int b)
{
	return a > (INT_MAX / b);
}

int ConvertToDecimal(const string &valueStr, int radix, bool &wasError)
{
	size_t i = 0;
	bool isNegativeNumber = false;
	if (valueStr[0] == SYMBOL_MINUS)
	{
		isNegativeNumber = true;
		i++;
	}
	int result = 0;
	for (; !wasError && i < valueStr.length(); ++i)
	{
		int digit = CharToDigit(valueStr[i]);
		int powNumber = static_cast<int>(pow(radix, (valueStr.length() - i - 1)));
		cout << digit << " " << powNumber << " " << "\n";
		if (Overflow(powNumber, digit, !isNegativeNumber))
		//if (isNegativeNumber &&)
		{
			wasError = true;
			cout << "Overflow" << "\n";
		}
		else
		{
			result += digit * powNumber;
		}
	}
	return isNegativeNumber ? -result : result;
}

string Radix(int srcNotation, int dstNotation, const string &srcValue, bool &wasError)
{
	int decimalNumber = ConvertToDecimal(srcValue, srcNotation, wasError);
	cout << "decimalNumber" << decimalNumber << "\n";
	string result;
	if (wasError)
	{
		return result;
	}
	if (decimalNumber == 0)
	{
		result = DIGITS[0];
		return result;
	}
	bool isNegativeNumber = false;
	if (decimalNumber < 0)
	{
		isNegativeNumber = true;
	}
	for (; decimalNumber != 0; decimalNumber = abs(decimalNumber) / dstNotation)
	{
		result += DigitToChar(abs(decimalNumber) % dstNotation);
	}
	reverse(result.begin(), result.end());
	return isNegativeNumber ? (SYMBOL_MINUS + result) : result;
}

bool Radix(int srcNotation, int dstNotation, const string &srcValue)
{
	bool wasError = false;
	string radix = Radix(srcNotation, dstNotation, srcValue, wasError);
	if (wasError)
	{
		cout << "Failed convert " << srcValue << " from " << srcNotation << " to " << dstNotation << "\n";
		return false;
	}
	cout << radix << "\n";
	return true;
}
