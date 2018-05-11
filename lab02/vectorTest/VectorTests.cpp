#include "pch.h"
#include "ProccessesVector.cpp"

TEST(VectorTest, EmptyVectorTest)
{
	std::vector<double> number = {};
	std::vector<double> checkNumber(number);
	VectorProcessor(number);
	ASSERT_EQ(number, checkNumber);
}

TEST(VectorTest, VectorWithOneNumber)
{
	std::vector<double> number = { 12 };
	std::vector<double> checkNumber = { 144 };
	VectorProcessor(number);
	ASSERT_EQ(number, checkNumber);
}

TEST(VectorTest, TheMinimumNumberIsEqualZero)
{
	std::vector<double> number = { 0, 1, 2, 3, 4, 5 };
	std::vector<double> checkNumber = { 0, 0, 0, 0, 0, 0 };
	VectorProcessor(number);
	ASSERT_EQ(number, checkNumber);
}

TEST(VectorTest, TheNegativeNumberIsMinimumNumber)
{
	std::vector<double> number = { -1, 1, 2, 3, 4, 5 };
	std::vector<double> checkNumber = { 1, -1, -2, -3, -4, -5 };
	VectorProcessor(number);
	ASSERT_EQ(number, checkNumber);
}

TEST(VectorTest, ThePositiveNumberIsMinimumNumber)
{
	std::vector<double> number = { 2, 3, 4, 5 };
	std::vector<double> checkNumber = { 4, 6, 8, 10 };
	VectorProcessor(number);
	ASSERT_EQ(number, checkNumber);
}