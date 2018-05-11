#include "stdafx.h"
#include "../geometricFigure/ColorRGBA.h"

namespace
{
void IsEqualColorRGBA(const ColorRGBA& verifiedClr, const ColorRGBA& expectedClr)
{
	REQUIRE((verifiedClr == expectedClr));
}

void ReadTest(std::istream& input, const ColorRGBA expectedClr, bool isSuccess)
{
	ColorRGBA clr;
	input >> clr;

	IsEqualColorRGBA(clr, expectedClr);
	REQUIRE(static_cast<bool>(input) == isSuccess);
}

void ReadTest(const std::string&when, const std::string& then, const std::string& inputStr, const ColorRGBA& expectedClr, bool isSuccess)
{
	AND_WHEN(when)
	{
		ColorRGBA clr;

		AND_THEN(then)
		{
			std::stringstream input(inputStr);
			ReadTest(input, expectedClr, isSuccess);
		}
	}
}
} // namespace

TEST_CASE("ColorRGBA test")
{
	GIVEN("point")
	{
		WHEN("declaring without passing variables to the constructor")
		{
			ColorRGBA clr;

			THEN("value a {0, 0, 0, 255}")
			{
				IsEqualColorRGBA(clr, { 0, 0, 0, 255});
			}
		}

		WHEN("declaring with transfer r, g, b and a")
		{
			ColorRGBA clr(254, 65, 194);

			THEN("value equal value {r, g, b, a}")
			{
				IsEqualColorRGBA(clr, { 254, 65, 194, 255 });
			}
		}

		WHEN("declaring with transfer other colorRGBA")
		{
			ColorRGBA expectedClr(54, 65, 194);
			ColorRGBA verifiedClr(expectedClr);

			THEN("value equal value {r, g, b, a}")
			{
				IsEqualColorRGBA(expectedClr, expectedClr);
			}
		}

		ReadTest("empty input", "failed read", "", { 0, 0, 0, 255 }, false);
		ReadTest("lack of components", "failed read", "3,3", { 0, 0, 0, 255 }, false);
		ReadTest("invalid delimeter", "failed read", "3$%3,3", { 0, 0, 0, 255 }, false);
		ReadTest("invalid r number", "failed read", "#,3,3", { 0, 0, 0, 255 }, false);
		ReadTest("invalid g number", "failed read", "3,#,3", { 0, 0, 0, 255 }, false);
		ReadTest("invalid b number", "failed read", "3,3,#", { 0, 0, 0, 255 }, false);
		ReadTest("valid rgba components", "success read", "3,3,3", { 3,3,3, 255 }, true);
	}
}
