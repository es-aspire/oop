#include "stdafx.h"
#include "CCanvas.h"


void CCanvas::DrawLine(sf::RenderTarget& target, const CPoint& from, const CPoint& to, const ColorRGBA& outlineColor) const
{
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(static_cast<float>(from.x), static_cast<float>(from.y)), sf::Color(outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a)),
		sf::Vertex(sf::Vector2f(static_cast<float>(to.x), static_cast<float>(to.y)), sf::Color(outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a))
	};

	target.draw(line, 2, sf::Lines);
}

void CCanvas::DrawCircle(sf::RenderTarget& target, double radius, const CPoint& center, const ColorRGBA& outlineColor, const ColorRGBA& fillColor) const
{
	constexpr int NUMBER_POINTS_IN_CIRCLE = 60;

	sf::CircleShape circle(radius, NUMBER_POINTS_IN_CIRCLE);

	circle.setPosition(static_cast<float>(center.x), static_cast<float>(center.y));

	circle.setOutlineColor(sf::Color(outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a));
	circle.setFillColor(sf::Color(fillColor.r, fillColor.g, fillColor.b, fillColor.a));
	circle.setOutlineThickness(3);
	target.draw(circle);
}

void CCanvas::DrawRectangle(sf::RenderTarget& target, const CPoint& position, double width, double height, const ColorRGBA& outlineColor, const ColorRGBA& fillColor) const
{
	sf::RectangleShape rect;

	rect.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
	rect.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));

	rect.setOutlineColor(sf::Color(outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a));
	rect.setFillColor(sf::Color(fillColor.r, fillColor.g, fillColor.b, fillColor.a));
	rect.setOutlineThickness(2);

	target.draw(rect);
}

void CCanvas::DrawPolygon(sf::RenderTarget& target, const Points& points, const ColorRGBA& outlineColor, const ColorRGBA& fillColor) const
{
	sf::ConvexShape polygon;

	polygon.setPointCount(points.size());

	for (size_t i = 0; i < points.size(); ++i)
	{
		polygon.setPoint(i, sf::Vector2f(static_cast<float>(points[i].x), static_cast<float>(points[i].y)));
	}

	polygon.setOutlineColor(sf::Color(outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a));
	polygon.setFillColor(sf::Color(fillColor.r, fillColor.g, fillColor.b, fillColor.a));

	polygon.setOutlineThickness(5);

	target.draw(polygon);
}