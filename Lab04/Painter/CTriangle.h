#pragma once
#include "Vec2.h"
#include "Shape.h"

class CTriangle : public CShape
{
public:
	CTriangle(Vec2 vertex1, Vec2 vertex2, Vec2 vertex3);

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