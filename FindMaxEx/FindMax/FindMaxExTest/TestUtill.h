#pragma once

namespace TestUtill
{

	template <typename T>
	struct VerifyFindMaxData
	{
	public:
		VerifyFindMaxData(std::string const& whenMsg,
			std::string const& thenMsg,
			std::vector<T> inputVector,
			T const& expectedValue,
			bool isSuccess = false)
			: whenMsg(whenMsg)
			, thenMsg(thenMsg)
			, inputVector(inputVector)
			, expectedValue(expectedValue)
			, isSuccess(isSuccess)
		{
		}

		std::string whenMsg;
		std::string thenMsg;
		std::vector<T> inputVector;
		T expectedValue;
		bool isSuccess;
	};

	template <typename T, typename Comparator = std::less<>>
	void VerifyFindMax(VerifyFindMaxData<T> const& data, Comparator const& comparator = Comparator())
	{
		AND_WHEN(data.whenMsg)
		{
			THEN(data.thenMsg)
			{
				T maxValue = T();

				REQUIRE(FindMax(data.inputVector, maxValue, comparator) == data.isSuccess);
				REQUIRE(static_cast<bool>(maxValue == data.expectedValue));
			}
		}
	}
}
