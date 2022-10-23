#pragma once
#include <vector>
#include "IShapeFactory.h"
#include "Rectangle.h"

class CShapeFactory : public IShapeFactory
{
public:
	ShapePointer CreateShape(std::string const& description) const override;
private:
	RectanglePointer CreateRectangle(std::vector<std::string> const& args) const;
};
