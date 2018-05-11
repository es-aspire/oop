#include "stdafx.h"
#include "primeNumber.h"

void Sieve(std::vector<bool> &primeNumbers, int upperBound)
{
	for (size_t i = 2; i < static_cast<size_t>(sqrt(upperBound)) + 1; ++i)
	{
		if (primeNumbers[i])
		{
			for (size_t j = i * i; j < primeNumbers.size(); j += i)
			{
				primeNumbers[j] = false;
			}
		}
	}
}

std::set<int> SearchPrimeNumber(const std::vector<bool> &primeNumber)
{
	std::set<int> result;

	for (size_t i = 2; i < primeNumber.size(); ++i)
	{
		if (primeNumber[i])
		{
			result.insert(result.end(), static_cast<int>(i));
		}
	}

	return result;
}

std::set<int> GeneratePrimeNumber(int upperBound)
{
	std::vector<bool> primeNumberVector(upperBound + 1, true);

	Sieve(primeNumberVector, upperBound);
	std::set<int> primeNumber = SearchPrimeNumber(primeNumberVector);

	return primeNumber;
}

void PrintPrimeNumber(std::ostream &output, const std::set<int> &primeNumbers)
{
	std::copy(primeNumbers.begin(), primeNumbers.end(), std::ostream_iterator<int>(output, " "));
	output << "\n";
}