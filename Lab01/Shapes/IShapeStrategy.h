#pragma once
#include <string>
#include "ICanvas.h"

class IShapeStrategy
{
public:
	virtual void Move(double dx, double dy) = 0;
	virtual void SetColor(Color const& color) = 0;

	virtual Color GetColor() const = 0;
	virtual std::string GetShapeInfo() const = 0;
	virtual std::string GetShapeName() const = 0;
	virtual void Draw(ICanvas& canvas) const = 0;
};
