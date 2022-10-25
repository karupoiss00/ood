#include <sstream>
#include "ShapeFactory.h"

using namespace std;

constexpr size_t SHAPE_NAME_ARGUMENT = 1;

ShapePointer CShapeFactory::CreateShape(std::string const& description) const
{
	ShapeParams params;
	stringstream stream(description);
	string token;

	stream >> params;

	try 
	{
		if (params.shapeName == "rectangle")
		{
			return CreateRectangle(params);
		}

		if (params.shapeName == "triangle")
		{
			return CreateTriangle(params);
		}
	}
	catch (exception const& e)
	{
		cout << e.what() << endl;
	}
	
	throw invalid_argument("invalid shape data");
}

RectanglePointer CShapeFactory::CreateRectangle(ShapeParams const& params) const
{
	if (params.vecs.size() < 2)
	{
		throw invalid_argument("not enough data for creating rectangle");
	}

	return make_unique<CRectangle>(params.vecs[0], params.vecs[1], params.color);
}

TrianglePointer CShapeFactory::CreateTriangle(ShapeParams const& params) const
{
	if (params.vecs.size() < 3)
	{
		throw invalid_argument("not enough data for creating triangle");
	}

	return make_unique<CTriangle>(params.vecs[0], params.vecs[1], params.vecs[2], params.color);
}