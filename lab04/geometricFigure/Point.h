#pragma once

class CPoint
{
public:
	CPoint();
	CPoint(int x0, int y0);

	void SetPoint(int x0, int y0);
	void SetPoint(const CPoint& point);

	int x;
	int y;
};

std::istream& operator >> (std::istream& input, CPoint& point);
bool operator==(const CPoint& verifiedPoint, const CPoint& expectedPoint);

