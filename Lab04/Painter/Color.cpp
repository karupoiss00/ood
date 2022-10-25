#include <iostream>
#include <stdexcept>
#include "Color.h"

using namespace std;

string ColorToString(Color color)
{
	switch (color)
	{
	case Color::GREEN:
		return "#228B22";
	case Color::RED:
		return "#F80000";
	case Color::BLUE:
		return "#42AAFF";
	case Color::YELLOW:
		return "#FEFE22";
	case Color::PINK:
		return "#FFA8AF";
	case Color::BLACK:
		return "#000000";
	default:
		throw invalid_argument("unknown color");
	}
}

Color ColorNameToColor(string const& colorName)
{
	if (colorName == "green")
	{
		return Color::GREEN;
	}
	if (colorName == "red")
	{
		return Color::RED;
	}
	if (colorName == "blue")
	{
		return Color::BLUE;
	}
	if (colorName == "yellow")
	{
		return Color::YELLOW;
	}
	if (colorName == "pink")
	{
		return Color::PINK;
	}
	if (colorName == "black")
	{
		return Color::BLACK;
	}

	return DEFAULT_COLOR;
}

std::istream& operator>>(istream& input, Color& rhs)
{
	string colorName;

	input >> colorName;

	rhs = ColorNameToColor(colorName);

	return input;
}