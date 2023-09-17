#pragma once
#include <string>

struct Color
{
	int r, g, b, a;

	std::string ToHex() const
	{
		return "#DEADBEEF";
	}
};

class ICanvas
{
public:
	virtual void MoveTo(double x, double y) = 0;
	virtual void SetColor(Color color) = 0;
	virtual void LineTo(double x, double y) = 0;
	virtual void DrawEllipse(double cx, double cy,  double rx, double ry) = 0;
	virtual void DrawText(double x, double y, std::string const& text) = 0;
};