#pragma once
#include <string>
#include "ICanvas.h"

class IShapeStrategy
{
public:
	virtual void Move(double dx, double dy) = 0;
	virtual void SetColor(sfx::Color const& color) = 0;

	virtual sfx::Color GetColor() const = 0;
	virtual std::string GetShapeInfo() const = 0;
	virtual std::string GetShapeName() const = 0;
	virtual void Draw(sfx::ICanvas& canvas) const = 0;
};
