#pragma once
#include <iostream>

struct Vec2
{
	Vec2(int x_, int y_)
		: x(x_), y(y_) {}
	int x;
	int y;
};

inline std::istream& operator>>(std::istream& input, Vec2& rhs)
{
	char ch;

	input >> ch >> rhs.x >> ch >> rhs.y >> ch;

	return input;
}