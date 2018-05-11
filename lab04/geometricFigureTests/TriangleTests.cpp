#include "stdafx.h"
#include "../geometricFigure/Triangle.cpp"

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

TEST_CASE("TriangleTest")
{
	SECTION("does allow to initialise three point on one line")
	{
		try
		{
			CTriangle triangle({ 0, 0 }, { 0, 476 }, { 0, 90 }, ColorRGBA(243, 76, 25), ColorRGBA(44, 86, 123));
		}
		catch (const std::exception& err)
		{
			std::stringstream strm;
			strm << err.what();
			
			REQUIRE(strm.str() == std::string("Is not triangle"));
		}
	}

	SECTION("allow to initialise valid triangle ")
	{
		try
		{
			CTriangle triangle({ 0, 0 }, { 90, 0 }, { 0, 90 }, ColorRGBA(243, 76, 25), ColorRGBA(44, 86, 123));
			REQUIRE(true);
		}
		catch (...)
		{
			REQUIRE(false);
		}
	}

	SECTION("allow to define triangle with default constructor")
	{
		CTriangle triangle;
		IsEqualPoint(triangle.GetVertexFirst(), { 0, 0 });
		IsEqualPoint(triangle.GetVertexSecond(), { 0, 90 });
		IsEqualPoint(triangle.GetVertexThrid(), { 90, 0 });

		REQUIRE(triangle.GetOutlineColor() == ColorRGBA(25, 25, 25));
		REQUIRE(triangle.GetFillColor() == ColorRGBA(25, 25, 25));
	}

	SECTION("allow to define triangle without color")
	{
		CTriangle triangle({ 20, 20 }, { 123, 432 }, { 12, 123 });
		IsEqualPoint(triangle.GetVertexFirst(), { 20, 20 });
		IsEqualPoint(triangle.GetVertexSecond(), { 123, 432 });
		IsEqualPoint(triangle.GetVertexThrid(), { 12, 123 });

		REQUIRE(triangle.GetOutlineColor() == ColorRGBA(25, 25, 25));
		REQUIRE(triangle.GetFillColor() == ColorRGBA(25, 25, 25));
	}

	CTriangle triangle({ 0, 0 }, { 90, 0 }, { 0, 90 }, ColorRGBA(243, 76, 25), ColorRGBA(44, 86, 123));

	SECTION("allow to get first vertex")
	{
		IsEqualPoint(triangle.GetVertexFirst(), { 0, 0 });
	}
	
	SECTION("allow to get second vertex")
	{
		IsEqualPoint(triangle.GetVertexSecond(), { 90, 0 });
	}

	SECTION("allow to get third vertex")
	{
		IsEqualPoint(triangle.GetVertexThrid(), { 0, 90 });
	}

	SECTION("allow get perimeter")
	{
		REQUIRE(IsEqualDouble(triangle.GetPerimeter(), 307.279));
	}

	SECTION("allow get area")
	{
		REQUIRE(IsEqualDouble(triangle.GetArea(), 4050));
	}

	SECTION("allow get outline color")
	{
		REQUIRE(triangle.GetOutlineColor() == ColorRGBA(243, 76, 25));
	}

	SECTION("allow set outline color")
	{
		triangle.SetOutlineColor(ColorRGBA(253, 65, 88));
		REQUIRE(triangle.GetOutlineColor() == ColorRGBA(253, 65, 88));
	}

	SECTION("allow get fill color")
	{
		REQUIRE(triangle.GetFillColor() == ColorRGBA(44, 86, 123));
	}

	SECTION("allow set fill color")
	{
		triangle.SetFillColor(ColorRGBA(253, 65, 88));
		REQUIRE(triangle.GetFillColor() == ColorRGBA(253, 65, 88));
	}

	SECTION("allow get info about line")
	{
		std::stringstream strm;
		std::string lineData = triangle.ToString();
		REQUIRE(lineData == std::string("Triangle:\t\n  - permiter: 3.1e+02\n  - area: 4.1e+03\n  - vertex first: (0, 0)\n  - vertex second: (90, 0)\n  - vertex third: (0, 90)\n  - outline color rgba: (243, 76, 25, 255)\n  - fill color rgba: (44, 86, 123, 255)\n"));
	}
}
