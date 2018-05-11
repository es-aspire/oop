#include "stdafx.h"
#include "Circle.h"

CCircle::CCircle()
	: m_center({ 0, 0 })
	, m_radius(20)
	, m_outlineColor(ColorRGBA(25, 25, 25))
	, m_fillColor(ColorRGBA(25, 25, 25))
{
}

CCircle::CCircle(const CPoint& center, double radius)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColor(ColorRGBA(25, 25, 25))
	, m_fillColor(ColorRGBA(25, 25, 25))
{}

CCircle::CCircle(const CPoint& center, double radius, const ColorRGBA& outlineColor, const ColorRGBA& fillColor)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

CCircle::~CCircle()
{
}

constexpr double PI = 3.14159;

double CCircle::GetArea() const
{
	return PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * PI * m_radius;
}

ColorRGBA CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

ColorRGBA CCircle::GetFillColor() const
{
	return m_fillColor;
}

void CCircle::SetOutlineColor(const ColorRGBA& color)
{
	m_outlineColor = color;
}

void CCircle::SetFillColor(const ColorRGBA& color)
{
	m_fillColor = color;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

std::string CCircle::ToString() const
{
	std::ostringstream strm;

	strm << std::setprecision(2)
		<< "Circle:\t" << std::endl
		<< "  - permiter: " << GetPerimeter() << std::endl
		<< "  - area: " << GetArea() << std::endl
		<< "  - radius: " << GetRadius() << std::endl
		<< "  - center: (" << m_center.x << ", " << m_center.y << ")" << std::endl 
		<< "  - outline color rgba: (" << m_outlineColor.r << ", " << m_outlineColor.g << ", " << m_outlineColor.b << ", " << m_outlineColor.a << ")" << std::endl
		<< "  - fill color rgba: (" << m_fillColor.r << ", " << m_fillColor.g << ", " << m_fillColor.b << ", " << m_fillColor.a << ")" << std::endl;

	return strm.str();
}

void CCircle::Draw(sf::RenderTarget& target, ICanvas& canvas) const
{
	canvas.DrawCircle(target, m_radius, m_center, m_outlineColor, m_fillColor);
}