#pragma once

#include "stdafx.h"
#include "Drawable.h"
#include "ColorRGBA.h"


class IShape : public IDrawable
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual ColorRGBA GetOutlineColor() const = 0;
	virtual void SetOutlineColor(const ColorRGBA& color) = 0;
	virtual void Draw(sf::RenderTarget& target, ICanvas& canvas) const = 0;
	
	virtual ~IShape() = default;
};
