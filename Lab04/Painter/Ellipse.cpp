#include "Ellipse.h"

CEllipse::CEllipse(Vec2 const& center, unsigned verticalRadius, unsigned horizontalRadius, Color color)
	: CShape(color), m_center(center), m_verticalRadius(verticalRadius), m_horizontalRadius(horizontalRadius)
{

}

void CEllipse::Draw(ICanvas& canvas) const
{
	canvas.SetColor(m_color);
	canvas.DrawEllipse(m_center, m_horizontalRadius, m_verticalRadius);
}

Vec2 CEllipse::GetCenter()
{
	return m_center;
}

unsigned CEllipse::GetVerticalRadius()
{
	return m_verticalRadius;
}

unsigned CEllipse::GetHorizontalRadius()
{
	return m_horizontalRadius;
}
