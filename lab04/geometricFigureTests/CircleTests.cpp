#include "stdafx.h"
#include "../geometricFigure/Circle.cpp"

namespace
{
	void IsEqualPoint(const CPoint& verifiedPoint, const CPoint& expectedPoint)
	{
		REQUIRE((verifiedPoint == expectedPoint));
	}

	bool IsEqualDouble(double numberFirst, double numberSecond)
	{
		return std::abs(numberFirst - numberSecond) < 1E-3;
	}
} // namespace

TEST_CASE("CircleTest")
{
	SECTION("allow to define circle with default constructor")
	{
		CCircle circle;
		IsEqualPoint(circle.GetCenter(), { 0, 0 });
		IsEqualDouble(circle.GetRadius(), 20.00);
		REQUIRE(circle.GetOutlineColor() == ColorRGBA(25, 25, 25));
		REQUIRE(circle.GetFillColor() == ColorRGBA(25, 25, 25));
	}

	SECTION("allow to define circle without color")
	{
		CCircle circle({ 30, 30 }, 40.00);
		IsEqualPoint(circle.GetCenter(), { 30, 30 });
		IsEqualDouble(circle.GetRadius(), 40.00);
		REQUIRE(circle.GetOutlineColor() == ColorRGBA(25, 25, 25));
		REQUIRE(circle.GetFillColor() == ColorRGBA(25, 25, 25));
	}

	CCircle circle({ 400, 300 }, 250, ColorRGBA(243, 76, 25), ColorRGBA(44, 86, 123));

	SECTION("allow get center")
	{
		IsEqualPoint(circle.GetCenter(), { 400, 300 });
	}

	SECTION("allow get radius")
	{
		IsEqualDouble(circle.GetRadius(), 250.00);
	}

	SECTION("allow get perimeter")
	{
		double x = circle.GetPerimeter();
		REQUIRE(IsEqualDouble(x, 1570.795));
	}

	SECTION("allow get area")
	{
		REQUIRE(IsEqualDouble(circle.GetArea(), 196349.375));
	}

	SECTION("allow get outline color")
	{
		REQUIRE(circle.GetOutlineColor() == ColorRGBA(243, 76, 25));
	}

	SECTION("allow set outline color")
	{
		circle.SetOutlineColor(ColorRGBA(253, 65, 88));
		REQUIRE(circle.GetOutlineColor() == ColorRGBA(253, 65, 88));
	}

	SECTION("allow get fill color")
	{
		REQUIRE(circle.GetFillColor() == ColorRGBA(44, 86, 123));
	}

	SECTION("allow set fill color")
	{
		circle.SetFillColor(ColorRGBA(253, 65, 88));
		REQUIRE(circle.GetFillColor() == ColorRGBA(253, 65, 88));
	}

	SECTION("allow get info about line")
	{
		std::stringstream strm;
		std::string lineData = circle.ToString();
		REQUIRE(lineData == std::string("Circle:\t\n  - permiter: 1.6e+03\n  - area: 2e+05\n  - radius: 2.5e+02\n  - center: (400, 300)\n  - outline color rgba: (243, 76, 25, 255)\n  - fill color rgba: (44, 86, 123, 255)\n"));
	}
}
