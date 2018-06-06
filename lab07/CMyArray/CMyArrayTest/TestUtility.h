#pragma once

namespace TestUtility
{

inline bool IsEqual(double lhs, double rhs)
{
	return std::abs(lhs - rhs) < std::numeric_limits<double>::epsilon();
}

template <typename T>
inline void VerifyArraySizeAndCapacity(CMyArray<T> const& arr, size_t expectedCapacity, size_t expectedSize)
{
	REQUIRE(arr.GetCapacity() == expectedCapacity);
	REQUIRE(arr.GetSize() == expectedSize);
}

template <typename T1, typename T2>
inline bool IsEqual(CMyArray<T1> const& arr, std::vector<T2> const& v)
{
	if (!arr.IsEmpty() && !v.empty())
	{
		if (arr.GetSize() != v.size())
		{
			return false;
		}

		for (size_t i = 0; i < arr.GetSize(); ++i)
		{
			if (arr[i] != v[i])
			{
				return false;
			}
		}
		return true;
	}

	return false;
}

template <typename T1, typename T2>
inline bool IsEqual(CMyArray<T1> const& arr, CMyArray<T2> const& v)
{
	if (!arr.IsEmpty() && !v.IsEmpty())
	{
		if (arr.GetSize() != v.GetSize())
		{
			return false;
		}

		for (size_t i = 0; i < arr.GetSize(); ++i)
		{
			if (arr[i] != v[i])
			{
				return false;
			}
		}
		return true;
	}

	return false;
}

}