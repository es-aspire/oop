#include "stdafx.h"
#include "Rectangle.h"
#include "Math.h"

CRectangle::CRectangle()
	: m_position({ 0, 0 })
	, m_width(10)
	, m_height(20)
	, m_outlineColor(ColorRGBA(25, 25, 25))
	, m_fillColor(ColorRGBA(25, 25, 25))
{
}

CRectangle::CRectangle(const CPoint& position, double width, double height)
	: m_position(position)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(ColorRGBA(25, 25, 25))
	, m_fillColor(ColorRGBA(25, 25, 25))
{
}

CRectangle::CRectangle(const CPoint& position, double width, double height, const ColorRGBA& outlineColor, const ColorRGBA& fillColor)
	: m_position(position)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

CRectangle::~CRectangle()
{
}

double CRectangle::GetArea() const
{
	return m_height * m_width;
}

double CRectangle::GetPerimeter() const
{
	return 2 * (m_height + m_width);
}

std::string CRectangle::ToString() const
{
	std::ostringstream strm;

	strm << std::setprecision(2)
		 << "Rectangle:\t" << std::endl
		 << "  - permiter: " << GetPerimeter() << std::endl
		 << "  - area: " << GetArea() << std::endl
		 << "  - width: " << GetWidth() << std::endl
		 << "  - height: " << GetHeight() << std::endl
		 << "  - position: (" << m_position.x << ", " << m_position.y << ")" << std::endl
		 << "  - outline color rgba: (" << m_outlineColor.r << ", " << m_outlineColor.g << ", " << m_outlineColor.b << ", " << m_outlineColor.a << ")" << std::endl
		 << "  - fill color rgba: (" << m_fillColor.r << ", " << m_fillColor.g << ", " << m_fillColor.b << ", " << m_fillColor.a << ")" << std::endl;

	return strm.str();
}

ColorRGBA CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

ColorRGBA CRectangle::GetFillColor() const
{
	return m_fillColor;
}

void CRectangle::SetOutlineColor(const ColorRGBA& color)
{
	m_outlineColor = color;
}

void CRectangle::SetFillColor(const ColorRGBA& color)
{
	m_fillColor = color;
}

CPoint CRectangle::GetPosition() const
{
	return m_position;
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_position;
}

CPoint CRectangle::GetRightBottom() const
{
	CPoint rightBottomPos;
	rightBottomPos.x = m_position.x + static_cast<int>(m_width);
	rightBottomPos.y = m_position.y + static_cast<int>(m_height);
	return rightBottomPos;
}

void CRectangle::Draw(sf::RenderTarget& target, ICanvas& canvas) const
{
	canvas.DrawRectangle(target, m_position, m_width, m_height, m_outlineColor, m_fillColor);
}
