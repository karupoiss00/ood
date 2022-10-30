#pragma once
#include <memory>
#include <string>
#include "Shape.h"

struct IShapeFactory
{
	virtual ShapePointer CreateShape(std::string const& description) = 0;

	virtual ~IShapeFactory() = default;
};