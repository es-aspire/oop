#pragma once
#include "Point.h"
#include "IShape.h"

class CLineSegment final : public IShape
{
public:
	CLineSegment();
	CLineSegment(const CPoint& startPoint, const CPoint& endPoint, const ColorRGBA& outlineColor);

	std::string ToString() const override;
	ColorRGBA GetOutlineColor() const override;
	void SetOutlineColor(const ColorRGBA& color) override;
	double GetArea() const override;
	double GetPerimeter() const override;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

	void SetStartPoint(int x, int y);
	void SetStartPoint(const CPoint& settablePoint);
	void SetEndPoint(int x, int y);
	void SetEndPoint(const CPoint& settablePoint);

	void Draw(sf::RenderTarget& target, ICanvas& canvas) const override;

	~CLineSegment();

private:
	CPoint m_startPoint;
	CPoint m_endPoint;

	ColorRGBA m_outlineColor;
};
