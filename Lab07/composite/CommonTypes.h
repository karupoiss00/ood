#pragma once
#include <numeric>

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