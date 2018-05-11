#pragma once
#include "Point.h"
#include "ISolidShape.h"

class CRectangle final : public ISolidShape
{
public:
	CRectangle();
	CRectangle(const CPoint& position, double width, double height);
	CRectangle(const CPoint& position, double width, double height, const ColorRGBA& outlineColor, const ColorRGBA& fillColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	ColorRGBA GetOutlineColor() const override;
	ColorRGBA GetFillColor() const override;
	void SetOutlineColor(const ColorRGBA& color) override;
	void SetFillColor(const ColorRGBA& color) override;

	CPoint GetPosition() const;
	double GetWidth() const;
	double GetHeight() const;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;

	void Draw(sf::RenderTarget& target, ICanvas& canvas) const override;

	~CRectangle();

private:
	double m_width;
	double m_height;
	CPoint m_position;

	ColorRGBA m_outlineColor;
	ColorRGBA m_fillColor;
};
