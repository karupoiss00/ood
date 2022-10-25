#pragma once
#include <vector>
#include <string>
#include "Vec2.h"
#include "Color.h"

struct ShapeParams
{
	std::string shapeName;
	Color color;
	std::vector<Vec2> vecs;
};

inline std::istream& operator>>(std::istream& input, ShapeParams& rhs)
{
	Vec2 vec(0, 0);

	input >> rhs.shapeName;
	input >> rhs.color;

	while (!input.eof())
	{
		input >> vec;
		rhs.vecs.push_back(vec);
	}

	return input;
}