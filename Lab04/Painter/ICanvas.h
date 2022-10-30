#pragma once
#include "Vec2.h"
#include "Color.h"

struct ICanvas
{
	virtual void SetColor(Color) = 0;
	virtual void DrawLine(Vec2 from, Vec2 to) = 0;
	virtual void DrawEllipse(Vec2 center, unsigned horizontalRadius, unsigned vertitalRadius) = 0;
};