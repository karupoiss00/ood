#pragma once
#include <iostream>
#include <string>
#include <memory>

#include "IShapeStrategy.h"
#include "CircleStrategy.h"
#include "LineStrategy.h"
#include "TextStrategy.h"
#include "TriangleStrategy.h"
#include "RectangleStrategy.h"

class ShapeStrategyFactory
{
public:
	static std::unique_ptr<IShapeStrategy> CreateFromStream(std::istream& input);
private:
	enum class ShapeType
	{
		CIRCLE,
		LINE,
		TEXT,
		TRIANGLE,
		RECTANGLE,
	};

	static ShapeType MapStringToShapeType(std::string str);
	static CircleStrategy CreateCircleStrategy(std::istream& input);
	static LineStrategy CreateLineStrategy(std::istream& input);
	static TextStrategy CreateTextStrategy(std::istream& input);
	static TriangleStrategy CreateTriangleStrategy(std::istream& input);
	static RectangleStrategy CreateRectangleStrategy(std::istream& input);
};