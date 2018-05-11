#include "stdafx.h"
#include "../geometricFigure/Rectangle.cpp"

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

TEST_CASE("RectangleTest")
{
	SECTION("allow to define rectangle with default constructor")
	{
		CRectangle rect;
		IsEqualPoint(rect.GetLeftTop(), { 0, 0 });
		IsEqualDouble(rect.GetWidth(), 10.00);
		IsEqualDouble(rect.GetHeight(), 20.00);
		REQUIRE(rect.GetOutlineColor() == ColorRGBA(25, 25, 25));
		REQUIRE(rect.GetFillColor() == ColorRGBA(25, 25, 25));
	}

	SECTION("allow to define rectangle without color")
	{
		CRectangle rect({ 30, 30 }, 240, 300);
		IsEqualPoint(rect.GetLeftTop(), { 30, 30 });
		IsEqualDouble(rect.GetWidth(), 240.00);
		IsEqualDouble(rect.GetHeight(), 300.00);
		REQUIRE(rect.GetOutlineColor() == ColorRGBA(25, 25, 25));
		REQUIRE(rect.GetFillColor() == ColorRGBA(25, 25, 25));
	}

	CRectangle rect({ 30, 30 }, 240, 300, ColorRGBA(243, 76, 25), ColorRGBA(44, 86, 123));

	SECTION("allow get start point")
	{
		IsEqualPoint(rect.GetPosition(), {30, 30});
	}

	SECTION("allow get left top point")
	{
		IsEqualPoint(rect.GetLeftTop(), { 30, 30 });
	}

	SECTION("allow get left top point")
	{
		IsEqualPoint(rect.GetRightBottom(), { 270, 330 });
	}

	SECTION("allow get width")
	{
		IsEqualDouble(rect.GetWidth(), 240.00);
	}

	SECTION("allow get height")
	{
		IsEqualDouble(rect.GetWidth(), 300);
	}

	SECTION("allow get perimeter")
	{
		REQUIRE(IsEqualDouble(rect.GetPerimeter(), 1080.00));
	}

	SECTION("allow get area")
	{
		REQUIRE(IsEqualDouble(rect.GetArea(), 72000.00));
	}

	SECTION("allow get outline color")
	{
		REQUIRE(rect.GetOutlineColor() == ColorRGBA(243, 76, 25));
	}

	SECTION("allow set outline color")
	{
		rect.SetOutlineColor(ColorRGBA(253, 65, 88));
		REQUIRE(rect.GetOutlineColor() == ColorRGBA(253, 65, 88));
	}

	SECTION("allow get fill color")
	{
		REQUIRE(rect.GetFillColor() == ColorRGBA(44, 86, 123));
	}

	SECTION("allow set fill color")
	{
		rect.SetFillColor(ColorRGBA(253, 65, 88));
		REQUIRE(rect.GetFillColor() == ColorRGBA(253, 65, 88));
	}

	SECTION("allow get info about line")
	{
		std::stringstream strm;
		std::string lineData = rect.ToString();
		REQUIRE(lineData == std::string("Rectangle:\t\n  - permiter: 1.1e+03\n  - area: 7.2e+04\n  - width: 2.4e+02\n  - height: 3e+02\n  - position: (30, 30)\n  - outline color rgba: (243, 76, 25, 255)\n  - fill color rgba: (44, 86, 123, 255)\n"));
	}
}
