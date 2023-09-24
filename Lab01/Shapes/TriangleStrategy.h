#pragma once
#include <array>
#include "Point.h"

class TriangleStrategy : public IShapeStrategy
{
public:
	TriangleStrategy(std::array<Point, 3> vertexes)
		: m_vertexes(vertexes)
	{}

	std::string GetShapeInfo() const final
	{
		std::string result = "";

		for (auto& vertex : m_vertexes)
		{
			result += " " + std::to_string(vertex.m_x)
					+ " " + std::to_string(vertex.m_y);
		}

		return result;
	}

	void Move(double dx, double dy) final
	{
		for (auto& vertex : m_vertexes)
		{
			vertex.m_x += dx;
			vertex.m_y += dy;
		}
	}

	void Draw(gfx::ICanvas& canvas) const final
	{
		canvas.MoveTo(m_vertexes[0].m_x, m_vertexes[0].m_y);
		canvas.LineTo(m_vertexes[1].m_x, m_vertexes[1].m_y);
		canvas.MoveTo(m_vertexes[1].m_x, m_vertexes[1].m_y);
		canvas.LineTo(m_vertexes[2].m_x, m_vertexes[2].m_y);
		canvas.MoveTo(m_vertexes[2].m_x, m_vertexes[2].m_y);
		canvas.LineTo(m_vertexes[0].m_x, m_vertexes[0].m_y);
	}

	std::string GetShapeName() const final
	{
		return "triangle";
	}
private:
	std::array<Point, 3> m_vertexes;
};