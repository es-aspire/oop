#include "stdafx.h"
#include "ProccessesVector.h"

std::vector<double> ReadVector(std::istream &input)
{
	std::vector<double> vector;
	
	copy(std::istream_iterator<double>(input), std::istream_iterator<double>(),
		std::back_inserter(vector));
	
	return vector;
}

void ProcessVector(std::vector<double> &number)
{
	if (!number.empty())
	{
		double minElement = *std::min_element(number.begin(), number.end());

		std::transform(number.begin(), number.end(), number.begin(), [&minElement](double number)
		{
			return minElement * number;
		});
	}
}

void PrintVector(std::ostream &output, std::vector<double> &vector)
{
	std::cout << std::fixed << std::setprecision(3);
	copy(vector.begin(), vector.end(), std::ostream_iterator<double>(output, " "));
	output << "\n";
}
