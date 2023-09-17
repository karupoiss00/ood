#pragma once
#include <array>
#include "ShapeStrategy.h"
#include "Point.h"

class TriangleStrategy : public ShapeStrategy
{
public:
	TriangleStrategy(std::array<Point, 3> vertexes, Color color)
		: ShapeStrategy(color),
		m_vertexes(vertexes)
	{}

	virtual std::string GetShapeInfo() const final
	{
		auto result = ShapeStrategy::GetShapeInfo();

		for (auto& vertex : m_vertexes)
		{
			result += " " + std::to_string(vertex.m_x)
					+ " " + std::to_string(vertex.m_y);
		}

		return result;
	}

	virtual void Move(double dx, double dy) final
	{
		for (auto& vertex : m_vertexes)
		{
			vertex.m_x += dx;
			vertex.m_y += dy;
		}
	}

	virtual void Draw(ICanvas& canvas) final
	{
		ShapeStrategy::Draw(canvas);

		canvas.MoveTo(m_vertexes[0].m_x, m_vertexes[0].m_y);
		canvas.LineTo(m_vertexes[1].m_x, m_vertexes[1].m_y);
		canvas.MoveTo(m_vertexes[1].m_x, m_vertexes[1].m_y);
		canvas.LineTo(m_vertexes[2].m_x, m_vertexes[2].m_y);
		canvas.MoveTo(m_vertexes[2].m_x, m_vertexes[2].m_y);
		canvas.LineTo(m_vertexes[0].m_x, m_vertexes[0].m_y);
	}
private:
	std::array<Point, 3> m_vertexes;
};