#pragma once
#include <numeric>
#include <iostream>

template <typename T>
struct Rect
{
	T left;
	T top;
	T width;
	T height;
};

template <typename T>
struct Point
{
	T x;
	T y;
};

using RectD = Rect<double>;
using PointD = Point<double>;
using RGBAColor = std::uint32_t;

inline bool operator==(PointD const& lhs, PointD const& rhs)
{
	return abs(lhs.x - rhs.x) < DBL_EPSILON && abs(lhs.y - rhs.y) < DBL_EPSILON;
}

inline bool operator==(RectD const& lhs, RectD const& rhs)
{
	return lhs.left == rhs.left 
		&& lhs.top == rhs.top
		&& lhs.width == rhs.width
		&& lhs.height == rhs.height;
}

inline std::ostream& operator<<(std::ostream& out, RectD const& value)
{
	out << "{ " 
		<< value.top << ", " 
		<< value.left << ", " 
		<< value.width << ", " 
		<< value.height 
	<< " }" << std::endl;

	return out;
}