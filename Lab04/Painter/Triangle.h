#pragma once
#include "Vec2.h"
#include "Shape.h"

class CTriangle : public CShape
{
public:
	CTriangle(Vec2 const& vertex1, Vec2 const& vertex2, Vec2 const& vertex3, Color color = DEFAULT_COLOR);

	void Draw(ICanvas& canvas) const override;
	
	Vec2 GetVertex1() const;
	Vec2 GetVertex2() const;
	Vec2 GetVertex3() const;

private:
	Vec2 m_vertex1;
	Vec2 m_vertex2;
	Vec2 m_vertex3;
};

using TrianglePointer = std::unique_ptr<CTriangle>;