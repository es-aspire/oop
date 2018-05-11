#include "stdafx.h"
#include "../geometricFigure/Point.cpp"

namespace
{
void IsEqualPoint(const CPoint& verifiedPoint, const CPoint& expectedPoint)
{
	REQUIRE((verifiedPoint == expectedPoint));
}

void ReadTest(std::stringstream& input, const CPoint expectedPoint, bool isSuccess)
{
	CPoint point;
	input >> point;

	IsEqualPoint(point, expectedPoint);
	REQUIRE(static_cast<bool>(input) == isSuccess);
}
} // namespace

TEST_CASE("Point test")
{
	GIVEN("point")
	{
		WHEN("declaring without passing variables to the constructor")
		{
			CPoint point;

			THEN("value a {0, 0}")
			{
				IsEqualPoint(point, { 0, 0 });
			}
		}

		WHEN("declaring with transfer x and y")
		{
			CPoint point(4, 6);

			THEN("value equal value {x, y}")
			{
				IsEqualPoint(point, { 4, 6 });
			}
		}

		WHEN("declaring with transfer other point")
		{
			CPoint expectedPoint(4, 6);
			CPoint verifiedPoint(expectedPoint);

			THEN("value equal value {x, y}")
			{
				IsEqualPoint(verifiedPoint, expectedPoint);
			}
		}

		AND_WHEN("allows you to set the coordinates with respect to x and y")
		{
			CPoint point(4, 6);

			THEN("value equal value {x, y}")
			{
				int x = 3;
				int y = 12;
				point.SetPoint(x, y);
				IsEqualPoint(point, { x, y });
			}
		}

		AND_WHEN("allows you to set the coordinates with tranfser other CPoint")
		{
			CPoint point(4, 6);

			THEN("value equal value {x, y}")
			{
				CPoint point1(44, 6);

				point.SetPoint(point1);
				IsEqualPoint(point, point1);
			}
		}

		AND_WHEN("empty input")
		{
			CPoint point;

			AND_THEN("failed read")
			{
				std::stringstream input("");
				ReadTest(input, { 0, 0 }, false);
			}
		}

		AND_WHEN("invalid x number")
		{
			CPoint point;

			AND_THEN("failed read")
			{
				std::stringstream input("#,3");
				ReadTest(input, { 0, 0 }, false);
			}
		}

		AND_WHEN("invalid delimeter of x and y")
		{
			CPoint point;

			AND_THEN("failed read")
			{
				std::stringstream input("2R3");
				ReadTest(input, { 0, 0 }, false);
			}
		}

		AND_WHEN("invalid y number")
		{
			CPoint point;

			AND_THEN("failed read")
			{
				std::stringstream input("53,%");
				ReadTest(input, { 0, 0 }, false);
			}
		}

		AND_WHEN("valid point")
		{
			AND_THEN("allow to read")
			{
				std::stringstream input("1,3");
				ReadTest(input, { 1, 3 }, true);
			}
		}
	}
}
