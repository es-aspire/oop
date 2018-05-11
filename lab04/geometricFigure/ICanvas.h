#pragma once

#include "ColorRGBA.h"
#include "Point.h"

using Points = std::vector<CPoint>;

class ICanvas
{
public:
	virtual void DrawLine(sf::RenderTarget& target, const CPoint& from, const CPoint& to, const ColorRGBA& outlineColor) const = 0;
	virtual void DrawCircle(sf::RenderTarget& target, double radius, const CPoint& center, const ColorRGBA& outlineColor, const ColorRGBA& fillColor) const = 0;
	virtual void DrawRectangle(sf::RenderTarget& target, const CPoint& position, double width, double height, const ColorRGBA& outlineColor, const ColorRGBA& fillColor) const = 0;
	virtual void DrawPolygon(sf::RenderTarget& target, const Points &points, const ColorRGBA& outlineColor, const ColorRGBA& fillColor) const = 0;

	virtual ~ICanvas() = default;
};
