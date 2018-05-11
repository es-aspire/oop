#pragma once

#include "IShape.h"

class ISolidShape : public IShape
{
public:
	virtual ColorRGBA GetFillColor() const = 0;
	virtual void SetFillColor(const ColorRGBA& color) = 0;
	virtual void Draw(sf::RenderTarget& target, ICanvas& canvas) const override = 0;

	virtual ~ISolidShape() = default;
};
