#include "RegularPolygon.h"

CRegularPolygon::CRegularPolygon(Vec2 const& center, unsigned radius, unsigned vertexCount, Color color)
	: CShape(color), m_center(center), m_radius(radius), m_vertexCount(vertexCount)
{

}

void CRegularPolygon::Draw(ICanvas& canvas) const
{
	canvas.SetColor(GetColor());

	const double pi = acos(-1);

	Vec2 from(m_center.x + m_radius, m_center.y);
	Vec2 to(0, 0);

	for (unsigned i = 1; i <= m_vertexCount; i++)
	{
		to.x = m_center.x + static_cast<int>(round(m_radius * cos(2 * pi * i / m_vertexCount)));
		to.y = m_center.y + static_cast<int>(round(m_radius * sin(2 * pi * i / m_vertexCount)));

		canvas.DrawLine(from, to);
		from = to;
	}
}

Vec2 CRegularPolygon::GetCenter() const
{
	return m_center;
}

unsigned CRegularPolygon::GetRadius() const
{
	return m_radius;
}

unsigned CRegularPolygon::GetVertexCount() const
{
	return m_vertexCount;
}