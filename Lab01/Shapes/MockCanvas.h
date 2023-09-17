#pragma once
#include <iostream>
#include "ICanvas.h"

class MockCanvas : public ICanvas
{
	void MoveTo(double x, double y) 
	{
		std::cout << "Move to " << x << " " << y << std::endl;
	}

	void SetColor(Color color)
	{
		std::cout << "Set color to " << color.ToHex() << std::endl;
	}

	void LineTo(double x, double y)
	{
		std::cout << "Line to " << x << " " << y << std::endl;
	}

	void DrawEllipse(double cx, double cy, double rx, double ry)
	{
		std::cout << "Draw ellipse " << cx << " " << cy << " " << rx << " " << ry << std::endl;
	}

	void DrawText(double x, double y, std::string const& text)
	{
		std::cout << "DrawText " << x << " " << y << " " << text << std::endl;
	}
};