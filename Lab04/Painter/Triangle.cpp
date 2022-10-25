#include "Triangle.h"

using namespace std;

CTriangle::CTriangle(Vec2 vertex1, Vec2 vertex2, Vec2 vertex3, Color color)
	: CShape(color), m_vertex1(vertex1), m_vertex2(vertex2), m_vertex3(vertex3)
{

}

void CTriangle::Draw(ICanvas& canvas) const
{
	canvas.SetColor(m_color);
	cout << "V1 " << m_vertex1.x << " " << m_vertex1.y << endl;
	cout << "V2 " << m_vertex2.x << " " << m_vertex2.y << endl;
	cout << "V3 " << m_vertex3.x << " " << m_vertex3.y << endl;
	canvas.DrawLine(m_vertex1, m_vertex2);
	canvas.DrawLine(m_vertex2, m_vertex3);
	canvas.DrawLine(m_vertex3, m_vertex1);
}

Vec2 CTriangle::GetVertex1() const
{
	return m_vertex1;
}

Vec2 CTriangle::GetVertex2() const
{
	return m_vertex2;
}

Vec2 CTriangle::GetVertex3() const
{
	return m_vertex3;
}
