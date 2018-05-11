#include "stdafx.h"
#include "LineSegment.h"
#include "Math.h"

CLineSegment::CLineSegment()
{
}

CLineSegment::CLineSegment(const CPoint& startPoint, const CPoint& endPoint, const ColorRGBA& outlineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_outlineColor(outlineColor)
{
}

CLineSegment::~CLineSegment()
{
}

std::string CLineSegment::ToString() const
{
	std::ostringstream strm;

	strm << std::setprecision(2)
		 << "Line segment:\t" << std::endl
		 << "  - start point: (" << m_startPoint.x << ", " << m_startPoint.y << ")" << std::endl
		 << "  - end point: (" << m_endPoint.x << ", " << m_endPoint.y << ")" << std::endl
		 << "  - area: " << GetArea() << std::endl
		 << "  - length: " << GetPerimeter() << std::endl
		 << "  - outline color rgba: (" << m_outlineColor.r << ", " << m_outlineColor.g << ", " << m_outlineColor.b << ", " << m_outlineColor.a << ")" << std::endl;

	return strm.str();
}

ColorRGBA CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

void CLineSegment::SetOutlineColor(const ColorRGBA& color)
{
	m_outlineColor = color;
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return Math::CalcLineLen(m_startPoint, m_endPoint);
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

void CLineSegment::SetStartPoint(int x, int y)
{
	m_startPoint.SetPoint(x, y);
}

void CLineSegment::SetStartPoint(const CPoint& settablePoint)
{
	m_startPoint.SetPoint(settablePoint);
}

void CLineSegment::SetEndPoint(int x, int y)
{
	m_endPoint.SetPoint(x, y);
}

void CLineSegment::SetEndPoint(const CPoint& settablePoint)
{
	m_endPoint.SetPoint(settablePoint);
}

void CLineSegment::Draw(sf::RenderTarget& target, ICanvas& canvas) const
{
	canvas.DrawLine(target, m_startPoint, m_endPoint, m_outlineColor);
}
