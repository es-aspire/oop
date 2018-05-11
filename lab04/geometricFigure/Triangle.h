#pragma once

#include "Point.h"
#include "ISolidShape.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle();
	CTriangle(const CPoint& vertexFirst, const CPoint& vertexSecond, const CPoint& vertexThird);
	CTriangle(const CPoint& vertexFirst, const CPoint& vertexSecond, const CPoint& vertexThird, const ColorRGBA& outlineColor, const ColorRGBA& fillColor);
	
	double GetPerimeter() const override;
	double GetArea() const override;
	std::string ToString() const override;

	ColorRGBA GetOutlineColor() const override;
	ColorRGBA GetFillColor() const override;
	void SetOutlineColor(const ColorRGBA& color) override; 
	void SetFillColor(const ColorRGBA& color) override;

	void Draw(sf::RenderTarget& target, ICanvas& canvas) const override;

	CPoint GetVertexFirst() const;
	CPoint GetVertexSecond() const;
	CPoint GetVertexThrid() const;

	~CTriangle();

private:
	bool IsTriangle() const;

private:
	CPoint m_vertexFirst;
	CPoint m_vertexSecond;
	CPoint m_vertexThird;

	ColorRGBA m_outlineColor;
	ColorRGBA m_fillColor;
};
