#pragma once

#include "Point.h"
#include <cmath>

namespace Math
{
inline double CalcLineLen(const CPoint& firstPoint, const CPoint& secondPoint)
{
	const int X1 = firstPoint.x;
	const int X2 = secondPoint.x;
	const int Y1 = firstPoint.y;
	const int Y2 = secondPoint.y;

	return std::sqrt((X2 - X1) * (X2 - X1) + (Y2 - Y1) * (Y2 - Y1));
}

inline bool IsEqual(double a, double b)
{
	return std::abs(a - b) < 1E-12;
}

inline bool IsColinearThreePoints(const CPoint& firstPoint, const CPoint& secondPoint, const CPoint& thirdPoint)
{
	double x1 = firstPoint.x;
	double y1 = firstPoint.x;
	double x2 = secondPoint.x;
	double y2 = secondPoint.y;
	double x3 = thirdPoint.x;
	double y3 = thirdPoint.y;

	return IsEqual((y3 - y2) * (x2 - x1) == (y2 - y1) * (x3 - x2), 0);
}
} // namespace Math
