#pragma once
#include <array>
#include <cassert>
#include "ShapeStrategyFactory.h"

using namespace std;

unique_ptr<IShapeStrategy> ShapeStrategyFactory::CreateFromStream(istream& input)
{
	string type;
	input >> type;

	ShapeType shape = MapStringToShapeType(type);

	switch (shape)
	{
	case ShapeType::CIRCLE:
		return make_unique<CircleStrategy>(CreateCircleStrategy(input));
	case ShapeType::LINE:
		return make_unique<LineStrategy>(CreateLineStrategy(input));
	case ShapeType::RECTANGLE:
		return make_unique<RectangleStrategy>(CreateRectangleStrategy(input));
	case ShapeType::TEXT:
		return make_unique<TextStrategy>(CreateTextStrategy(input));
	case ShapeType::TRIANGLE:
		return make_unique<TriangleStrategy>(CreateTriangleStrategy(input));
	default:
		break;
	}

	throw exception("unknown shape");
}

ShapeStrategyFactory::ShapeType ShapeStrategyFactory::MapStringToShapeType(string str)
{
	if (str == "circle")
	{
		return ShapeType::CIRCLE;
	}
	else if (str == "line")
	{
		return ShapeType::LINE;
	}
	else if (str == "rectangle")
	{
		return ShapeType::RECTANGLE;
	}
	else if (str == "text")
	{
		return ShapeType::TEXT;
	}
	else if (str == "triangle")
	{
		return ShapeType::TRIANGLE;
	}
	else
	{
		auto msg = "unknown shape type: " + str;
		throw exception(msg.c_str());
	}
}


CircleStrategy ShapeStrategyFactory::CreateCircleStrategy(istream& input)
{
	string cxStr, cyStr, rStr;

	input >> cxStr >> cyStr >> rStr;

	if (cxStr.empty() || cyStr.empty() || rStr.empty())
	{
		throw exception("invalid circle arguments, template: <center x> <center y> <radius>");
	}

	try 
	{
		double cx = stod(cxStr);
		double cy = stod(cxStr);
		double r = stod(cxStr);

		return CircleStrategy(Point{ cx, cy }, r);
	}
	catch (...)
	{
		throw exception("can not parse numbers");
	}
}

LineStrategy ShapeStrategyFactory::CreateLineStrategy(istream& input)
{
	string x1Str, y1Str, x2Str, y2Str;

	input >> x1Str >> y1Str >> x2Str >> y2Str;

	if (x1Str.empty() || y1Str.empty() || x2Str.empty() || y2Str.empty())
	{
		throw exception("invalid line arguments, template: <x1> <y1> <x2> <y2>");
	}

	try
	{
		double x1 = stod(x1Str);
		double y1 = stod(y1Str);
		double x2 = stod(x2Str);
		double y2 = stod(y2Str);

		return LineStrategy(Point{ x1, y1 }, Point{ x2, y2 });
	}
	catch (...)
	{
		throw exception("can not parse numbers");
	}
}

TextStrategy ShapeStrategyFactory::CreateTextStrategy(istream& input)
{
	string xStr, yStr, fontSizeStr, text;

	input >> xStr >> yStr >> fontSizeStr;

	string str;
	while (!input.eof())
	{
		input >> str;
		text += str;
	}

	if (xStr.empty() || yStr.empty() || fontSizeStr.empty() || text.empty())
	{
		throw exception("invalid text arguments, template: <left> <top> <size> <text>");
	}

	try
	{
		double x = stod(xStr);
		double y = stod(yStr);
		double fontSize = stod(fontSizeStr);

		return TextStrategy(Point{ x, y }, fontSize, move(text));
	}
	catch (...)
	{
		throw exception("can not parse numbers");
	}
}

TriangleStrategy ShapeStrategyFactory::CreateTriangleStrategy(istream& input)
{
	array<string, 6> argsStr;

	for (auto& arg : argsStr)
	{
		input >> arg;
	}

	for (auto const& arg : argsStr)
	{
		if (arg.empty())
		{
			throw exception("invalid triangle arguments, template: <x1> <y1> <x2> <y2> <x3> <y3>");
		}
	}

	try
	{
		array<double, 6> args;
		
		for (unsigned i = 0; i < 6; i++)
		{
			args[i] = stod(argsStr[i]);
		}

		return TriangleStrategy(
			{ 
				Point{ args[0], args[1] },
				Point{ args[2], args[3] },
				Point{ args[4], args[5] } 
			}
		);
	}
	catch (...)
	{
		throw exception("can not parse numbers");
	}
}

RectangleStrategy ShapeStrategyFactory::CreateRectangleStrategy(istream& input)
{
	array<string, 4> argsStr;

	for (auto& arg : argsStr)
	{
		input >> arg;
	}

	for (auto const& arg : argsStr)
	{
		if (arg.empty())
		{
			throw exception("invalid rectangle arguments, template: <left> <top> <width> <height>");
		}
	}

	try
	{
		array<double, 4> args;

		for (unsigned i = 0; i < 4; i++)
		{
			args[i] = stod(argsStr[i]);
		}

		return RectangleStrategy(
			Point{ args[0], args[1] },
			args[2],
			args[3]
		);
	}
	catch (...)
	{
		throw exception("can not parse numbers");
	}
}
