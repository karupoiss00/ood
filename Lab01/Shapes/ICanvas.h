#pragma once
#include <string>
#include <regex>
#include "Color.h"

namespace sfx
{
	class ICanvas
	{
	public:
		virtual void MoveTo(double x, double y) = 0;
		virtual void SetColor(Color color) = 0;
		virtual void LineTo(double x, double y) = 0;
		virtual void DrawEllipse(double cx, double cy, double rx, double ry) = 0;
		virtual void DrawText(double x, double y, double fontSize, std::string const& text) = 0;
	};
}

