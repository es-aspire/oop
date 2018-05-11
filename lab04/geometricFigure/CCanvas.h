#pragma once
#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
	void DrawLine(sf::RenderTarget& target, const CPoint& from, const CPoint& to, const ColorRGBA& outlineColor) const override;
	virtual void DrawCircle(sf::RenderTarget& target, double radius, const CPoint& center, const ColorRGBA& outlineColor, const ColorRGBA& fillColor) const override;
	void DrawRectangle(sf::RenderTarget& target, const CPoint& position, double width, double height, const ColorRGBA& outlineColor, const ColorRGBA& fillColor) const override;
	void DrawPolygon(sf::RenderTarget& target, const Points& points, const ColorRGBA& outlineColor, const ColorRGBA& fillColor) const override;
};
