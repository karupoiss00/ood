#pragma once
#include "Vec2.h"
#include "Shape.h"

class CRectangle : public CShape
{
public:
	CRectangle();
	CRectangle(Vec2 const& leftTop, Vec2 const& rightBottom, Color color = DEFAULT_COLOR);

	void Draw(ICanvas& canvas) const override;
	Vec2 GetLeftTop() const;
	Vec2 GetRightBottomTop() const;
private:
	Vec2 m_leftTop;
	Vec2 m_rightBottom;
};

using RectanglePointer = std::unique_ptr<CRectangle>;