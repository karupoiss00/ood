#pragma once
#include <string>
#include "ICanvas.h"

class IShapeStartegy
{
public:
	virtual std::string GetShapeInfo() const = 0;
	virtual void Move(double dx, double dy) = 0;
	virtual void Draw(ICanvas& canvas) = 0;
	virtual void SetColor(Color const& color) = 0;
};
