#pragma once
#include "Point.h"
#include "ISolidShape.h"

class CCircle : public ISolidShape
{
public:
	CCircle();
	CCircle(const CPoint& center, double radius);

	CCircle(const CPoint& center, double radius, const ColorRGBA& outlineColor, const ColorRGBA& fillColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	ColorRGBA GetOutlineColor() const override;
	ColorRGBA GetFillColor() const override;
	void SetOutlineColor(const ColorRGBA& color) override;
	void SetFillColor(const ColorRGBA& color) override;

	double GetRadius() const;
	CPoint GetCenter() const;

	void Draw(sf::RenderTarget& target, ICanvas& canvas) const override;

	~CCircle();

private:
	CPoint m_center;
	double m_radius = 0.0;

	ColorRGBA m_outlineColor;
	ColorRGBA m_fillColor;
};
