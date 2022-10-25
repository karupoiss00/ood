#include "Shape.h"

CShape::CShape()
{

}

CShape::CShape(Color color)
	: m_color(color)
{

}
void CShape::Fill(Color color)
{
	m_color = color;
}

Color CShape::GetColor() const
{
	return m_color;
}

CShape::~CShape()
{
}
