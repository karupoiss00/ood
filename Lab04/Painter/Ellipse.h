#pragma once
#include "Vec2.h"
#include "Shape.h"

class CEllipse : public CShape
{
public:
	CEllipse(Vec2 const& center, unsigned verticalRadius, unsigned horizontalRadius, Color color = DEFAULT_COLOR);

	void Draw(ICanvas& canvas) const override;

	Vec2 GetCenter();
	unsigned GetVerticalRadius();
	unsigned GetHorizontalRadius();
private:
	Vec2 m_center;
	unsigned m_verticalRadius;
	unsigned m_horizontalRadius;
};

using EllipsePointer = std::unique_ptr<CEllipse>;