#pragma once
#include "IShapes.h"
#include "IDrawable.h"

class ISlide : public IDrawable
{
public:
	virtual ~ISlide() = default;

	virtual double GetWidth() const = 0;
	virtual double GetHeight() const = 0;

	virtual IShapes& GetShapes() = 0;
};