#pragma once
#include <vector>
#include <string>
#include "Vec2.h"
#include "Color.h"

struct ShapeParams
{
	std::string shapeName;
	Color color;
	std::vector<std::string> params;
};

inline std::istream& operator>>(std::istream& input, ShapeParams& rhs)
{
	std::string param;

	input >> rhs.shapeName;
	input >> rhs.color;

	while (!input.eof())
	{
		input >> param;
		rhs.params.push_back(param);
	}

	return input;
}