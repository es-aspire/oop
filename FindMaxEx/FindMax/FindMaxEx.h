#pragma once

#include <functional>
#include <vector>

template <typename T, typename Less = std::less<>>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less = Less())
{
	if (arr.empty())
	{
		return false;
	}

	maxValue = arr[0];

	for (const auto& item : arr)
	{
		if (less(maxValue, item))
		{
			maxValue = item;
		}
	}

	return true;
}
