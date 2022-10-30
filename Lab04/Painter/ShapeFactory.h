#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <map>
#include "IShapeFactory.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "RegularPolygon.h"
#include "ShapeParams.h"

class CShapeFactory : public IShapeFactory
{
public:	
	CShapeFactory();

	ShapePointer CreateShape(std::string const& description) override;
private:
	using ActionMap = std::map<std::string, std::function<ShapePointer(ShapeParams const&)>>;

	void CreateActionMap();

	RectanglePointer CreateRectangle(ShapeParams const& params) const;
	TrianglePointer CreateTriangle(ShapeParams const& params) const;
	EllipsePointer CreateEllipse(ShapeParams const& params) const;
	RegularPolygonPointer CreateRegularPolygon(ShapeParams const& params) const;

	ActionMap m_actionMap;
};
