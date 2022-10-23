#include <sstream>
#include "ShapeFactory.h"

using namespace std;

constexpr size_t SHAPE_NAME_ARGUMENT = 1;

ShapePointer CShapeFactory::CreateShape(std::string const& description) const
{
	vector<string> tokens;
	stringstream stream(description);
	string token;

	while (!stream.eof())
	{
		stream >> token;
		tokens.push_back(token);
	}

	unsigned argumentsCount = tokens.size() - SHAPE_NAME_ARGUMENT;

	if (argumentsCount == 4)
	{
		if (*tokens.cbegin() == "rectangle")
		{
			return CreateRectangle(tokens);
		}
	}
	
	return make_unique<CRectangle>();
}

RectanglePointer CShapeFactory::CreateRectangle(vector<string> const& args) const
{
	int left = atoi(args[1].c_str());
	int top = atoi(args[2].c_str());
	int rigth = atoi(args[3].c_str());
	int bottom = atoi(args[4].c_str());

	Vec2 leftTop(left, top);
	Vec2 rightBottom(rigth, bottom);

	return make_unique<CRectangle>(leftTop, rightBottom);
}