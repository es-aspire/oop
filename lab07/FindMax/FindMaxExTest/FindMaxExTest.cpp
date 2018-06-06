#include "stdafx.h"
#include "../FindMaxEx.h"
#include "Sportsman.h"
#include "TestUtill.h"
#include "Vector2D.h"

using namespace TestUtill;
	
SCENARIO("FindMaxEx, default comparator")
{
	GIVEN("default comparassion")
	{
		{
			VerifyFindMaxData<int> verifyData("input vector of int is empty",
				"return false and variable 'maxValue' is equal a initial value",
				{}, 0, false);

			VerifyFindMax(verifyData);
		}
		{
			VerifyFindMaxData<int> verifyData("input vector of int is not empty",
				"return true",
				{ -1, 0, 2, 3 }, 3, true);

			VerifyFindMax(verifyData);
		}

		AND_WHEN("input vector of struct is not empty")
		{

			std::vector<Sportsman> sportsmans = {
				{ "Ovechkin", 180, 110 },
				{ "Chara", 208, 114 },
				{ "Crosby", 180, 90 },
				{ "Panarin", 180, 80 }
			};
			{
				VerifyFindMaxData<Sportsman> verifyData("struct/class has an operator '<'",
					"return true",
					sportsmans, Sportsman("Panarin", 180, 80), true);

				VerifyFindMax(verifyData);
			}
		}
	}
}

SCENARIO("FindMaxEx, custom comparator")
{
	GIVEN("custom comparassion")
	{
		{
			std::vector<int> v = { 1, 2, 3, -4, 55, -56, 45 };
			int expectedOutput = 55;

			VerifyFindMaxData<int> verifyData("when not empty vector of int",
				"return true",
				v, expectedOutput, true);

			VerifyFindMax(verifyData);
		}
		{
			std::vector<Sportsman> sportsmans = {
				{ "Ovechkin", 180, 110 },
				{ "Chara", 208, 114 },
				{ "Crosby", 180, 90 },
				{ "Panarin", 180, 80 }
			};
			Sportsman expectedSportsman("Chara", 208, 114);

			VerifyFindMaxData<Sportsman> verifyData("when not empty vector of Sportsman",
				"search for the grouth athlete",
				sportsmans, expectedSportsman, true);

			auto comparator = [](Sportsman const& lhs, Sportsman const& rhs) {
				return lhs.growth < rhs.growth;
			};

			VerifyFindMax(verifyData, comparator);
		}
	}
}
