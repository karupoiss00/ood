#pragma once
#include <vector>
#include "IShapeFactory.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "ShapeParams.h"

class CShapeFactory : public IShapeFactory
{
public:
	ShapePointer CreateShape(std::string const& description) const override;
private:
	RectanglePointer CreateRectangle(ShapeParams const& params) const;
	TrianglePointer CreateTriangle(ShapeParams const& params) const;
};
