#include "stdafx.h"
#include "Point.h"

CPoint::CPoint()
	: x(0)
	, y(0)
{
}

CPoint::CPoint(int x0, int y0)
	: x(x0)
	, y(y0)
{
}

void CPoint::SetPoint(int x0, int y0)
{
	x = x0;
	y = y0;
}

void CPoint::SetPoint(const CPoint& point)
{
	x = point.x;
	y = point.y;
}

std::istream& operator >> (std::istream& input, CPoint& point)
{
	int x = 0;
	int y = 0;

	if (input >> x && input.get() == ',' && input >> y)
	{
		point = CPoint(x, y);
	}
	else
	{
		input.setstate(std::ios_base::failbit | input.rdstate());
	}

	return input;
}

bool operator==(const CPoint& verifiedPoint, const CPoint& expectedPoint)
{
	return verifiedPoint.x == expectedPoint.x && verifiedPoint.y == expectedPoint.y;
}