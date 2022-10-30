#include <sstream>
#include "ShapeFactory.h"

using namespace std;

constexpr size_t SHAPE_NAME_ARGUMENT = 1;

CShapeFactory::CShapeFactory()
{
	CreateActionMap();
}

ShapePointer CShapeFactory::CreateShape(std::string const& description)
{
	ShapeParams params;
	stringstream stream(description);
	string token;

	stream >> params;

	if (m_actionMap.find(params.shapeName) == m_actionMap.end())
	{
		throw invalid_argument("invalid shape name");
	}

	return m_actionMap[params.shapeName](params);
}

void CShapeFactory::CreateActionMap()
{
	m_actionMap.clear();

	m_actionMap.insert(make_pair("rectangle", bind(&CShapeFactory::CreateRectangle, this, placeholders::_1)));
	m_actionMap.insert(make_pair("triangle", bind(&CShapeFactory::CreateTriangle, this, placeholders::_1)));
	m_actionMap.insert(make_pair("ellipse", bind(&CShapeFactory::CreateEllipse, this, placeholders::_1)));
	m_actionMap.insert(make_pair("regular_polygon", bind(&CShapeFactory::CreateRegularPolygon, this, placeholders::_1)));
}

RectanglePointer CShapeFactory::CreateRectangle(ShapeParams const& params) const
{
	if (params.params.size() < 2)
	{
		throw invalid_argument("not enough data for creating rectangle");
	}
	Vec2 topLeft = StringToVec2(params.params[0]);
	Vec2 rightBottom = StringToVec2(params.params[1]);

	return make_unique<CRectangle>(topLeft, rightBottom, params.color);
} 

TrianglePointer CShapeFactory::CreateTriangle(ShapeParams const& params) const
{
	if (params.params.size() < 3)
	{
		throw invalid_argument("not enough data for creating triangle");
	}

	Vec2 vertex1 = StringToVec2(params.params[0]);
	Vec2 vertex2 = StringToVec2(params.params[1]);
	Vec2 vertex3 = StringToVec2(params.params[2]);

	return make_unique<CTriangle>(vertex1, vertex2, vertex3, params.color);
}

EllipsePointer CShapeFactory::CreateEllipse(ShapeParams const& params) const
{
	if (params.params.size() < 3)
	{
		throw invalid_argument("not enough data for creating ellipse");
	}

	Vec2 center = StringToVec2(params.params[0]);
	unsigned verticalRadius = static_cast<unsigned>(stoul(params.params[1].c_str()));
	unsigned horizontalRadius = static_cast<unsigned>(stoul(params.params[2].c_str()));

	return make_unique<CEllipse>(center, verticalRadius, horizontalRadius, params.color);
}

RegularPolygonPointer CShapeFactory::CreateRegularPolygon(ShapeParams const& params) const
{
	if (params.params.size() < 3)
	{
		throw invalid_argument("not enough data for creating regular polygon");
	}

	Vec2 center = StringToVec2(params.params[0]);
	unsigned radius = static_cast<unsigned>(stoul(params.params[1].c_str()));
	unsigned vertexCount = static_cast<unsigned>(stoul(params.params[2].c_str()));

	return make_unique<CRegularPolygon>(center, radius, vertexCount, params.color);
}