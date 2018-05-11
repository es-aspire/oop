#include "stdafx.h"
#include "../rational/Rational.cpp"
#include <numeric>

namespace
{
void CheckValueOfRationalNumber(CRational const& rationalNumber, int numerator, int denominator)
{
	REQUIRE(rationalNumber.GetNumerator() == numerator);
	REQUIRE(rationalNumber.GetDenominator() == denominator);
}

bool IsEqual(double lhs, double rhs)
{
	return std::abs(lhs - rhs) < 1E-7;
}
} // namespace

void VerifiyFailedRead(std::istream& strm)
{
	THEN("failed read")
	{
		CRational lhs;

		strm >> lhs;

		REQUIRE_FALSE(static_cast<bool>(strm));
	}
}

void VerifyCompoundFacrtion(CRational const& number, int expectedIntger, double expectedCompoundFraction)
{
	auto compoundFraction = number.ToCompoundFraction();

	REQUIRE(compoundFraction.first == expectedIntger);
	REQUIRE(IsEqual(compoundFraction.second.ToDouble(), expectedCompoundFraction));
}

TEST_CASE("CRational test")
{
	GIVEN("Initially")
	{
		WHEN("Declare rational number without parameter")
		{
			CRational number;

			THEN("zero is constructed")
			{
				CheckValueOfRationalNumber(number, 0, 1);
			}
		}

		WHEN("Declare rational number without parameter")
		{
			CRational number;

			THEN("zero is constructed")
			{
				CheckValueOfRationalNumber(number, 0, 1);
			}
		}

		WHEN("declare rational number with only numerator")
		{
			CRational number(2);

			THEN("numerator is equal a passed to the constructor number, denumerator = 1")
			{
				CheckValueOfRationalNumber(number, 2, 1);
			}
		}

		WHEN("declare rational number with numerator and denominator")
		{
			WHEN("denominator < 0")
			{
				CRational number(5, -2);

				THEN("numerator change the sign")
				{
					CheckValueOfRationalNumber(number, -5, 2);
				}
			}

			WHEN("denominator == 0")
			{
				CRational number(5, 0);

				THEN("numerator is equal 0 and denumerator is equal a 1")
				{
					CheckValueOfRationalNumber(number, 0, 1);
				}
			}

			WHEN("denominator > 0")
			{
				CRational number(5, 2);

				THEN("numerator and denumerator is equal a passed to the constructor numbers")
				{
					CheckValueOfRationalNumber(number, 5, 2);
				}
			}
		}

		THEN("allow convert rational number to double")
		{
			CRational number(5, 2);

			REQUIRE(IsEqual(number.ToDouble(), 2.5));
			REQUIRE(IsEqual(2.5, number.ToDouble()));
		}

		THEN("allow get compound fraction")
		{
			WHEN("positive number")
			{
				AND_WHEN("not a zero integer part")
				{
					CRational number(5, 2);

					VerifyCompoundFacrtion(CRational(5, 2), 2, 0.5);
				}
				
				AND_WHEN("zero integer part")
				{
					VerifyCompoundFacrtion(CRational(1, 2), 0, 0.5);
				}
			}

			WHEN("negative number")
			{
				AND_WHEN("not a zero integer part")
				{
					VerifyCompoundFacrtion(CRational(-5, 2), -2, 0.5);
				}
				
				AND_WHEN("zero integer part")
				{
					VerifyCompoundFacrtion(CRational(-1, 2), 0, -0.5);
				}
			}

			WHEN("numerator == 0")
			{
				VerifyCompoundFacrtion(CRational(), 0, 0.0);
			}
		}

		THEN("Unary '-' returns a rational number with the opposite sign")
		{
			CRational number(5, 2);

			number = -number;

			CheckValueOfRationalNumber(number, -5, 2);
		}

		THEN("Unary '+' returns a rational number equal to the current one")
		{
			CRational number(5, 2);

			number = +number;

			CheckValueOfRationalNumber(number, 5, 2);
		}

		THEN("Binary '+' Returns the result of addition of two rational numbers")
		{
			CRational lhs(1, 2);
			CRational rhs(1, 6);

			rhs = lhs + rhs;

			CheckValueOfRationalNumber(rhs, 2, 3);
		}

		THEN("Binary '+' Returns the result of addition of rational number with integer")
		{
			CRational lhs(1, 2);

			lhs = lhs + 1;

			CheckValueOfRationalNumber(lhs, 3, 2);
		}

		THEN("Binary '+' Returns the result of addition of integer number with rational")
		{
			CRational lhs(1, 2);

			lhs = 1 + lhs;

			CheckValueOfRationalNumber(lhs, 3, 2);
		}

		THEN("Binary '-' Returns the result of difference of two rational numbers")
		{
			CRational lhs(1, 2);
			CRational rhs(3, 2);

			lhs = lhs - rhs;

			CheckValueOfRationalNumber(lhs, -1, 1);
		}

		THEN("Binary '+' Returns the result of difference of two number: rational with integer")
		{
			CRational lhs(1, 2);

			lhs = lhs - 1;

			CheckValueOfRationalNumber(lhs, -1, 2);
		}

		THEN("Binary + Returns the result of addition of two number: integer with rational")
		{
			CRational lhs(1, 2);

			lhs = 1 - lhs;

			CheckValueOfRationalNumber(lhs, 1, 2);
		}

		THEN("'+=' Performs an increase in the rational number by the value of the second rational")
		{
			CRational lhs(1, 2);
			CRational rhs(1, 6);

			lhs += rhs;

			CheckValueOfRationalNumber(lhs, 2, 3);
		}

		THEN("'+=' Performs an increase in the rational number by an integer")
		{
			CRational lhs(1, 2);

			lhs += 1;

			CheckValueOfRationalNumber(lhs, 3, 2);
		}

		THEN("'-=' Performs an increase in the rational number by the value of the second rational")
		{
			CRational lhs(1, 2);
			CRational rhs(1, 6);

			lhs -= rhs;

			CheckValueOfRationalNumber(lhs, 1, 3);
		}

		THEN("'-=' Performs an increase in the rational number by an integer")
		{
			CRational lhs(1, 2);

			lhs -= 1;

			CheckValueOfRationalNumber(lhs, -1, 2);
		}

		THEN("'*' Returns the result of the product of rational numbers")
		{
			CRational lhs(1, 2);
			CRational rhs(2, 3);

			lhs = lhs * rhs;

			CheckValueOfRationalNumber(lhs, 1, 3);
		}

		THEN("'*' Returns the result of the product of the rational and the integer numbers")
		{
			CRational lhs(1, 2);

			lhs = lhs * -3;

			CheckValueOfRationalNumber(lhs, -3, 2);
		}

		THEN("'*' Returns the result of the product of the integer and the rational numbers")
		{
			CRational lhs(2, 3);

			lhs = 7 * lhs;

			CheckValueOfRationalNumber(lhs, 14, 3);
		}

		THEN("'/' Returns the result of the divide of rational numbers")
		{
			CRational lhs(1, 2);
			CRational rhs(2, 3);

			lhs = lhs / rhs;

			CheckValueOfRationalNumber(lhs, 3, 4);
		}

		THEN("'/' Returns the result of the divide of the rational and the integer numbers")
		{
			CRational lhs(1, 2);

			lhs = lhs / 5;

			CheckValueOfRationalNumber(lhs, 1, 10);
		}

		THEN("'/' Returns the result of the divide of the integer and the rational numbers")
		{
			CRational lhs(2, 3);

			lhs = 7 / lhs;

			CheckValueOfRationalNumber(lhs, 21, 2);
		}

		THEN("'*=' Returns the result of the product of the rational and the integer numbers")
		{
			CRational lhs(1, 2);
			CRational rhs(2, 3);

			lhs *= rhs;

			CheckValueOfRationalNumber(lhs, 1, 3);
		}

		THEN("'*=' Returns the result of the product of the integer and the rational numbers")
		{
			CRational lhs(3, 2);

			lhs *= 3;

			CheckValueOfRationalNumber(lhs, 9, 2);
		}

		THEN("'/=' Returns the result of the divide of the rational and the integer numbers")
		{
			CRational lhs(1, 2);
			CRational rhs(2, 3);

			lhs /= rhs;

			CheckValueOfRationalNumber(lhs, 3, 4);
		}

		THEN("'/=' Returns the result of the divide of the integer and the rational numbers")
		{
			CRational lhs(1, 2);

			lhs /= 3;

			CheckValueOfRationalNumber(lhs, 1, 6);
		}

		THEN("'=='Check the equality of two rational numbers")
		{
			CRational lhs(1, 2);
			CRational rhs(6, 2);

			REQUIRE(lhs == lhs);
			REQUIRE_FALSE(lhs == rhs);
		}

		THEN("'=='Check the equality of two numbers: integer and rational")
		{
			CRational rhs(4);

			REQUIRE(4 == rhs);
			REQUIRE_FALSE(99 == rhs);
		}

		THEN("'!='Check the inequality of two rational numbers")
		{
			CRational lhs(4);
			CRational rhs(46, 123);

			REQUIRE(lhs != rhs);
			REQUIRE_FALSE(lhs != lhs);
		}

		THEN("'!='Check the inequality of two numbers: integer and rational")
		{
			CRational rhs(1);

			REQUIRE(4 != rhs);
			REQUIRE_FALSE(1 != rhs);
		}

		THEN("'!='Check the equality of two numbers: rational and integer")
		{
			CRational lhs(1);

			REQUIRE(lhs != 4);
			REQUIRE_FALSE(lhs != 1);
		}

		THEN("'<' compare two rational number")
		{
			CRational lhs1(1, 32);
			CRational rhs(1, 2);

			REQUIRE(lhs1 < rhs);
			
			CRational lhs2(5);

			REQUIRE_FALSE(lhs2 < rhs);
		}

		THEN("'<' compare two numbers: rational and integer")
		{
			CRational lhs(1, 32);

			REQUIRE(lhs < 1);
			REQUIRE_FALSE(lhs < -10);
		}

		THEN("'<' compare two numbers: integer and rational ")
		{
			CRational lhs(1, 32);

			REQUIRE(0 < lhs);
			REQUIRE_FALSE(10 < lhs);
		}
		THEN("'<=' compare two rational number")
		{
			CRational lhs1(1, 32);
			CRational rhs(1, 2);

			REQUIRE(lhs1 <= rhs);

			CRational lhs2(5);

			REQUIRE_FALSE(lhs2 <= rhs);
		}

		THEN("'<=' compare two numbers: rational and integer")
		{
			CRational lhs(1, 32);

			REQUIRE(lhs <= 1);
			REQUIRE_FALSE(lhs <= -10);
		}

		THEN("'<=' compare two numbers: integer and rational ")
		{
			CRational lhs(1, 32);

			REQUIRE_FALSE(10 <= lhs);
			REQUIRE(0 <= lhs);
		}

		THEN("'>' compare two rational numbers")
		{
			CRational lhs1(1, 32);
			CRational rhs(1, 2);

			REQUIRE_FALSE(lhs1 > rhs);

			CRational lhs2(5);
			
			REQUIRE(lhs2 > rhs);
		}

		THEN("'>' compare two numbers: rational and integer")
		{
			CRational lhs1(1, 32);
			CRational lhs2(5);

			REQUIRE_FALSE(lhs1 > 1);
			REQUIRE(lhs2 > 1);
		}

		THEN("'>' compare two numbers: integer and rational")
		{
			CRational lhs1(1, 32);
			
			REQUIRE_FALSE(0 > lhs1);
			
			CRational lhs2(1, 32);
			
			REQUIRE(5 > lhs2);
		}

		THEN("'>=' compare two rational numbers")
		{
			CRational lhs1(1, 32);
			CRational rhs(1, 2);

			REQUIRE_FALSE(lhs1 >= rhs);
			
			CRational lhs2(12, 1);

			REQUIRE(lhs2 >= rhs);
		}

		THEN("'>=' compare two numbers: rational and integer")
		{
			CRational lhs(1, 32);

			REQUIRE_FALSE(lhs >= 32);
			REQUIRE(lhs >= 0);
		}

		THEN("'>=' compare two numbers: integer and rational")
		{
			CRational lhs(1, 32);

			REQUIRE_FALSE(0 >= lhs);
			REQUIRE(1 >= lhs);
		}

		THEN("output rational number")
		{
			CRational lhs(1, 32);

			std::stringstream strm;
			strm << lhs;

			REQUIRE(strm.str() == "1/32");
		}

		THEN("read reational number")
		{
			WHEN("invalid numerator")
			{
				std::stringstream strm("#/12");

				VerifiyFailedRead(strm);
			}

			WHEN("invalid delimeter")
			{
				std::stringstream strm("12$12");

				VerifiyFailedRead(strm);
			}

			WHEN("invalid denominator")
			{
				std::stringstream strm("12/$");

				VerifiyFailedRead(strm);
			}

			WHEN("all component of rational number is valid")
			{
				std::stringstream strm("12/14");

				THEN("success read")
				{
					CRational number;

					strm >> number;

					CheckValueOfRationalNumber(number, 6, 7);
				}
			}
		}

		THEN("output rational")
		{
			CRational number(1, 4);
			std::stringstream strm;

			strm << number;

			REQUIRE(strm.str() == "1/4");
		}

		THEN("output Fraction")
		{
			WHEN("numerator is not equal zero")
			{
				CRational number(5, 4);
				CRational::CompoundFraction fraction = number.ToCompoundFraction();

				std::stringstream strm;

				strm << fraction;

				REQUIRE(strm.str() == "1 1/4");
			}

			WHEN("numerator is equal zero")
			{
				CRational number(1, 4);
				CRational::CompoundFraction fraction = number.ToCompoundFraction();

				std::stringstream strm;

				strm << fraction;

				REQUIRE(strm.str() == "1/4");
			}
		}
	}
}
