#pragma once

#include <functional>
#include <vector>

template <typename T, typename Less = std::less<T>>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less = Less())
{
	if (arr.empty())
	{
		return false;
	}

	auto maxIt = arr.begin();

	for (auto it = maxIt + 1; it != arr.end(), ++it)
	{
		if (less(*maxIt, *it))
		{
			maxIt = it;
		}
	}

	maxValue = *maxIt;
	return true;
}
