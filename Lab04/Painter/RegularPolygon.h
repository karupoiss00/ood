#pragma once
#include "Vec2.h"
#include "Shape.h" 

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(Vec2 const& center, unsigned radius, unsigned vertexCount, Color color = DEFAULT_COLOR);

	void Draw(ICanvas& canvas) const override;

	Vec2 GetCenter() const;
	unsigned GetRadius() const;
	unsigned GetVertexCount() const;

private:
	Vec2 m_center;
	unsigned m_radius;
	unsigned m_vertexCount;
};

using RegularPolygonPointer = std::unique_ptr<CRegularPolygon>;