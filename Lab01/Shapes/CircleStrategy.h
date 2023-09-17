#pragma once
#include "ShapeStrategy.h"
#include "Point.h"

class CircleStrategy : public ShapeStrategy
{
public:
	CircleStrategy(Point center, double radius, Color color)
		: ShapeStrategy(color),
		m_center(center),
		m_radius(radius)
	{}

	virtual std::string GetShapeInfo() const final
	{
		return ShapeStrategy::GetShapeInfo()
			+ " " + std::to_string(m_center.m_x)
			+ " " + std::to_string(m_center.m_y)
			+ " " + std::to_string(m_radius);
	}

	virtual void Move(double dx, double dy) final
	{
		m_center.m_x += dx;
		m_center.m_y += dy;
	}

	virtual void Draw(ICanvas& canvas) final
	{
		ShapeStrategy::Draw(canvas);

		canvas.DrawEllipse(m_center.m_x, m_center.m_y, m_radius, m_radius);
	}
private:
	Point m_center;
	double m_radius;
};