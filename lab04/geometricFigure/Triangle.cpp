#include "stdafx.h"
#include "Triangle.h"
#include "Math.h"

CTriangle::CTriangle()
	: m_vertexFirst({ 0, 0 })
	, m_vertexSecond({ 0, 90 })
	, m_vertexThird({ 90 ,0})
	, m_outlineColor(ColorRGBA(25, 25, 25))
	, m_fillColor(ColorRGBA(25, 25, 25))
{
}

CTriangle::CTriangle(const CPoint& vertexFirst, const CPoint& vertexSecond, const CPoint& vertexThird)
	: m_vertexFirst(vertexFirst)
	, m_vertexSecond(vertexSecond)
	, m_vertexThird(vertexThird)
	, m_outlineColor(ColorRGBA(25, 25, 25))
	, m_fillColor(ColorRGBA(25, 25, 25))
{
}

CTriangle::CTriangle(const CPoint& vertexFirst, const CPoint& vertexSecond, const CPoint& vertexThird, const ColorRGBA& outlineColor, const ColorRGBA& fillColor)
	: m_vertexFirst(vertexFirst)
	, m_vertexSecond(vertexSecond)
	, m_vertexThird(vertexThird)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
	if (!IsTriangle())
	{
		throw std::logic_error("Is not triangle");
	}
}

CTriangle::~CTriangle()
{
}

double CTriangle::GetPerimeter() const
{
	return Math::CalcLineSegmentLength(m_vertexFirst, m_vertexSecond) + Math::CalcLineSegmentLength(m_vertexFirst, m_vertexThird) + Math::CalcLineSegmentLength(m_vertexSecond, m_vertexThird);
}

double CTriangle::GetArea() const
{
	double p = 0.5 * GetPerimeter();

	return std::sqrt(p
		* (p - Math::CalcLineSegmentLength(m_vertexFirst, m_vertexSecond))
		* (p - Math::CalcLineSegmentLength(m_vertexFirst, m_vertexThird))
		* (p - Math::CalcLineSegmentLength(m_vertexSecond, m_vertexThird)));
}

std::string CTriangle::ToString() const
{
	std::ostringstream strm;

	strm << std::setprecision(2)
		 << "Triangle:\t" << std::endl
		 << "  - permiter: " << GetPerimeter() << std::endl
		 << "  - area: " << GetArea() << std::endl
		 << "  - vertex first: (" << m_vertexFirst.x << ", " << m_vertexFirst.y << ")" << std::endl
		 << "  - vertex second: (" << m_vertexSecond.x << ", " << m_vertexSecond.y << ")" << std::endl
		 << "  - vertex third: (" << m_vertexThird.x << ", " << m_vertexThird.y << ")" << std::endl
		 << "  - outline color rgba: (" << m_outlineColor.r << ", " << m_outlineColor.g << ", " << m_outlineColor.b << ", " << m_outlineColor.a << ")" << std::endl
		 << "  - fill color rgba: (" << m_fillColor.r << ", " << m_fillColor.g << ", " << m_fillColor.b << ", " << m_fillColor.a << ")" << std::endl;

	return strm.str();
}

ColorRGBA CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

ColorRGBA CTriangle::GetFillColor() const
{
	return m_fillColor;
}

void CTriangle::SetOutlineColor(const ColorRGBA& color)
{
	m_outlineColor = color;
}

void CTriangle::SetFillColor(const ColorRGBA& color)
{
	m_fillColor = color;
}

void CTriangle::Draw(sf::RenderTarget& target, ICanvas& canvas) const
{
	Points points;
	points.push_back(m_vertexFirst);
	points.push_back(m_vertexSecond);
	points.push_back(m_vertexThird);

	canvas.DrawPolygon(target, points, m_outlineColor, m_fillColor);
}


CPoint CTriangle::GetVertexFirst() const
{
	return m_vertexFirst;
}

CPoint CTriangle::GetVertexSecond() const
{
	return m_vertexSecond;
}

CPoint CTriangle::GetVertexThrid() const
{
	return m_vertexThird;
}

bool CTriangle::IsTriangle() const
{
	return Math::IsColinearThreePoints(m_vertexFirst, m_vertexSecond, m_vertexThird);
}
