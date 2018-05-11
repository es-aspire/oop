#include "pch.h"
#include "PrimeNumber.cpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

void GeneratePrimeNumberTest(int upperBound, const vector<int> &primeNumbersVect)
{
	std::set<int> check;

	for (const auto &item : primeNumbersVect)
	{
		check.insert(item);
	}

	std::set<int> primeNumbers = GeneratePrimeNumber(upperBound);
	EXPECT_EQ(check, primeNumbers);
}

TEST(PrimeNumberTest, upper_bound_is_less_min_valid_number)
{
	GeneratePrimeNumberTest(1, {});
}

TEST(PrimeNumberTest, upper_bound_is_equal_min_valid_number)
{
	GeneratePrimeNumberTest(2, { 2 });
}

TEST(PrimeNumberTest, two_prime_number)
{
	GeneratePrimeNumberTest(3, { 2, 3 });
}

TEST(PrimeNumberTest, three_prime_number)
{
	GeneratePrimeNumberTest(5, { 2, 3, 5 });
}

TEST(PrimeNumberTest, four_prime_number)
{
	GeneratePrimeNumberTest(7, { 2, 3, 5, 7 });
}

TEST(PrimeNumberTest, upper_bound_is_equal_max_valid_number)
{
	std::chrono::time_point<std::chrono::system_clock> start;
	
	start = std::chrono::system_clock::now();
	
	std::set<int> primeNumbers = GeneratePrimeNumber(100000000);

	std::chrono::time_point<std::chrono::system_clock> end;
	end = std::chrono::system_clock::now();
	int elapsedMilliseconds = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>
		(end - start).count());
	int maxElapsedMilliseconds = 12000;
	int countValidPrimeNumber = 5761455;

	EXPECT_LE(elapsedMilliseconds, maxElapsedMilliseconds);
	EXPECT_EQ(countValidPrimeNumber, primeNumbers.size());
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
