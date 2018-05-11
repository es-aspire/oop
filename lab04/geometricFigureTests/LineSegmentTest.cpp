#include "stdafx.h"
#include "../geometricFigure/ColorRGBA.h"
#include "../geometricFigure/LineSegment.cpp"

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

TEST_CASE("LineSegment")
{
	SECTION("allow to define circle with default constructor")
	{
		CLineSegment line;
		IsEqualPoint(line.GetStartPoint(), { 0, 0 });
		IsEqualPoint(line.GetEndPoint(), { 0, 0 });
		REQUIRE(line.GetOutlineColor() == ColorRGBA(0, 0, 0));
	}
	CLineSegment line({ 30, 30 }, { 400, 400 }, ColorRGBA(26, 85, 124));

	SECTION("allow get start point")
	{
		IsEqualPoint(line.GetStartPoint(), { 30, 30 });
	}

	SECTION("allow get end point")
	{
		IsEqualPoint(line.GetEndPoint(), { 400, 400 });
	}
	SECTION("set start point by x, y")
	{
		line.SetStartPoint(20, 20);
		IsEqualPoint(line.GetStartPoint(), { 20, 20 });
	}

	SECTION("set start point by point")
	{
		line.SetStartPoint({ 27, 60 });
		IsEqualPoint(line.GetStartPoint(), { 27, 60 });
	}

	SECTION("set end point by x, y")
	{
		line.SetEndPoint(20, 20);
		IsEqualPoint(line.GetEndPoint(), { 20, 20 });
	}

	SECTION("set end point by point")
	{
		line.SetEndPoint({ 27, 60 });
		IsEqualPoint(line.GetEndPoint(), { 27, 60 });
	}

	SECTION("allow get perimeter")
	{
		REQUIRE(IsEqualDouble(line.GetPerimeter(), 523.26));
	}

	SECTION("area is equal a zero")
	{
		REQUIRE(IsEqualDouble(line.GetArea(), 0));
	}

	SECTION("allow get outline color")
	{
		REQUIRE(line.GetOutlineColor() == ColorRGBA(26, 85, 124));
	}

	SECTION("allow set outline color")
	{
		line.SetOutlineColor(ColorRGBA(253, 65, 88));
		REQUIRE(line.GetOutlineColor() == ColorRGBA(253, 65, 88));
	}

	SECTION("allow get info about line")
	{
		std::stringstream strm;
		std::string lineData = line.ToString();
		REQUIRE(lineData == std::string("Line segment:\t\n  - start point: (30, 30)\n  - end point: (400, 400)\n  - area: 0\n  - length: 5.2e+02\n  - outline color rgba: (26, 85, 124, 255)\n"));
	}
}
