#pragma once
#include "ICanvas.h"

class IDrawable
{
public:
	virtual void Draw(sf::RenderTarget& target, ICanvas& canvas) const = 0;

	virtual ~IDrawable() = default;
};

