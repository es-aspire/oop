#include "stdafx.h"
#include "../calculator/CalculatorController.cpp"

SCENARIO("Test utills")
{
	GIVEN("Tests IsDouble")
	{
		WHEN("input string is empty")
		{
			REQUIRE(!IsDouble(""));
		}

		AND_WHEN("input string contains only one invalid character")
		{
			REQUIRE(!IsDouble("#"));
		}

		AND_WHEN("input string contains only sign character")
		{
			REQUIRE(!IsDouble("+"));
			REQUIRE(!IsDouble("-"));
		}

		AND_WHEN("input string contains only one number character")
		{
			REQUIRE(IsDouble("0"));
			REQUIRE(IsDouble("1"));
			REQUIRE(IsDouble("2"));
			REQUIRE(IsDouble("3"));
			REQUIRE(IsDouble("4"));
		}

		AND_WHEN("input string contains valid two-digit number")
		{
			REQUIRE(IsDouble("12"));
			REQUIRE(IsDouble("78"));
			REQUIRE(IsDouble("32"));
		}

		AND_WHEN("input string contains valid ten-digit number without")
		{
			REQUIRE(IsDouble("120000000"));
			REQUIRE(IsDouble("782356532"));
			REQUIRE(IsDouble("326443563"));
		}
		
		AND_WHEN("input string contains valid two-digit number with valid digit after floating point")
		{
			REQUIRE(IsDouble("12.0012"));
			REQUIRE(IsDouble("78.235341"));
			REQUIRE(IsDouble("32.7345"));
		}

		AND_WHEN("input string contains valid ten-digit number with valid digit after floating point")
		{
			REQUIRE(IsDouble("120000000.0012"));
			REQUIRE(IsDouble("782356532.235376543"));
			REQUIRE(IsDouble("326443563.7345"));
		}

		AND_WHEN("input string contains valid two-digit number witho invalid digit after floating point")
		{
			REQUIRE(!IsDouble("12.00@12#"));
			REQUIRE(!IsDouble("78.235%3%41"));
			REQUIRE(!IsDouble("32.73$@45"));
		}

		AND_WHEN("input string contains valid ten-digit number with invalid digit after floating point")
		{
			REQUIRE(!IsDouble("120000000.00&12"));
			REQUIRE(!IsDouble("782356532.235*3(76543"));
			REQUIRE(!IsDouble("326443563.734E TF5"));
		}

		AND_WHEN("input string contains invalid character at beginning")
		{
			REQUIRE(!IsDouble("@120000000"));
		}

		AND_WHEN("input string contains invalid characters at middle")
		{
			REQUIRE(!IsDouble("3264%^43563"));
		}

		AND_WHEN("input string contains invalid characters at ending")
		{
			REQUIRE(!IsDouble("326443563^%"));
		}
	}

	SECTION("Test IsValidIdentifier")
	{
		SECTION("empty input string")
		{
			REQUIRE(!IsValidIdentifier(""));
		}

		SECTION("input string does contains not characters of the English alphabet, numbers and underscore")
		{
			REQUIRE(!IsValidIdentifier("Q1@$@!@"));
			REQUIRE(!IsValidIdentifier("%$$@"));
		}

		SECTION("first characters is not numbers and remaining characters are English characters, numbers and underscores")
		{
			REQUIRE(!IsValidIdentifier("1wW24er"));
			REQUIRE(!IsValidIdentifier("5wW24er"));
		}

		SECTION("first characters is English characters, underscores and remaining characters are English characters, numbers or underscores")
		{
			REQUIRE(IsValidIdentifier("m_var"));
			REQUIRE(IsValidIdentifier("_var"));
			REQUIRE(IsValidIdentifier("_var_"));
			REQUIRE(IsValidIdentifier("_var_Name"));
		}

		SECTION("first characters is English characters, underscores and remaining characters are not English characters, numbers or underscores")
		{
			REQUIRE(!IsValidIdentifier("m_var!@#"));
			REQUIRE(!IsValidIdentifier("_var!#"));
			REQUIRE(!IsValidIdentifier("_var@$_"));
			REQUIRE(!IsValidIdentifier("_var_Na$^me"));
		}
	}
}