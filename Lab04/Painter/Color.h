#pragma once
#include <string>

enum class Color 
{
	GREEN,
	RED,
	BLUE,
	YELLOW,
	PINK,
	BLACK,
};

constexpr Color DEFAULT_COLOR = Color::BLACK;

std::string ColorToString(Color color);
Color ColorNameToColor(std::string const& colorName);
std::istream& operator>>(std::istream& input, Color& rhs);