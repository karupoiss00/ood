#include "Rectangle.h"


CRectangle::CRectangle()
	: m_leftTop({ 0, 0 }), m_rightBottom({ 1, 1 })
{

}


CRectangle::CRectangle(Vec2 const& leftTop, Vec2 const& rightBottom, Color color)
	: CShape(color), m_leftTop(leftTop), m_rightBottom(rightBottom)
{

}

void CRectangle::Draw(ICanvas& canvas) const
{
	Vec2 rightTop(m_rightBottom.x, m_leftTop.y);
	Vec2 leftBottom(m_leftTop.x, m_rightBottom.y);

	canvas.SetColor(m_color);

	canvas.DrawLine(m_leftTop, rightTop);
	canvas.DrawLine(rightTop, m_rightBottom);
	canvas.DrawLine(m_rightBottom, leftBottom);
	canvas.DrawLine(leftBottom, m_leftTop);
}

Vec2 CRectangle::GetLeftTop() const
{
	return m_leftTop;
}
Vec2 CRectangle::GetRightBottomTop() const
{
	return m_rightBottom;
}