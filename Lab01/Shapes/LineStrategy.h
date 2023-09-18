#pragma once
#include "ShapeStrategy.h"
#include "Point.h"

class LineStrategy : public ShapeStrategy
{
public:
	LineStrategy(Point startPoint, Point endPoint)
		: m_startPoint(startPoint),
		m_endPoint(endPoint)
	{}

	std::string GetShapeInfo() const final
	{
		return ShapeStrategy::GetShapeInfo()
			+ " " + std::to_string(m_startPoint.m_x)
			+ " " + std::to_string(m_startPoint.m_y)
			+ " " + std::to_string(m_endPoint.m_x)
			+ " " + std::to_string(m_endPoint.m_y);
	}

	void Move(double dx, double dy) final
	{
		m_startPoint.m_x += dx;
		m_startPoint.m_y += dy;
		m_endPoint.m_x += dx;
		m_endPoint.m_y += dy;
	}

	void Draw(sfx::ICanvas& canvas) const final
	{
		ShapeStrategy::Draw(canvas);

		canvas.MoveTo(m_startPoint.m_x, m_startPoint.m_y);
		canvas.LineTo(m_endPoint.m_x, m_endPoint.m_y);
	}

	std::string GetShapeName() const final
	{
		return "line";
	}
private:
	Point m_startPoint;
	Point m_endPoint;
};