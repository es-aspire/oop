#include "pch.h"
#include "ProccessesVector.cpp"

void ProcessVectorTest(std::vector<double> &number, std::vector<double> &checkNumber)
{
	ProcessVector(number);
	ASSERT_EQ(number, checkNumber);
}

TEST(Vector_test, empty_vector_test)
{
	std::vector<double> number = {};
	std::vector<double> checkNumber = {};
	ProcessVectorTest(number, checkNumber);
}

TEST(Vector_test, vector_with_one_number)
{
	std::vector<double> number = { 12};
	std::vector<double> checkNumber = { 144 };
	ProcessVectorTest(number, checkNumber);
}

TEST(Vector_test, the_minimum_number_is_equal_zero)
{
	std::vector<double> number = { 0, 1, 2, 3, 4, 5 };
	std::vector<double> checkNumber = { 0, 0, 0, 0, 0, 0 };
	ProcessVectorTest(number, checkNumber);
}

TEST(Vector_test, the_minimum_number_is_negative_number)
{
	std::vector<double> number = { -1, 1, 2, 3, 4, 5 };
	std::vector<double> checkNumber = { 1, -1, -2, -3, -4, -5 };
	ProcessVectorTest(number, checkNumber);
}

TEST(Vector_test, the_minimum_number_is_positive_number)
{
	std::vector<double> number = { 2, 3, 4, 5 };
	std::vector<double> checkNumber = { 4, 6, 8, 10 };
	ProcessVectorTest(number, checkNumber);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
