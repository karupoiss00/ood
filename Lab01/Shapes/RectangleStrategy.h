#pragma once
#include "ShapeStrategy.h"
#include "Point.h"

class RectangleStrategy : public ShapeStrategy
{
public:
	RectangleStrategy(Point startPoint, double width, double height)
		: m_startPoint(startPoint), 
		m_width(width), 
		m_height(height)
	{}

	std::string GetShapeInfo() const final
	{
		return ShapeStrategy::GetShapeInfo()
			+ " " + std::to_string(m_startPoint.m_x)
			+ " " + std::to_string(m_startPoint.m_y)
			+ " " + std::to_string(m_width)
			+ " " + std::to_string(m_height);
	}

	void Move(double dx, double dy) final
	{
		m_startPoint.m_x += dx;
		m_startPoint.m_y += dy;
	}

	void Draw(sfx::ICanvas& canvas) const final
	{
		ShapeStrategy::Draw(canvas);

		canvas.MoveTo(m_startPoint.m_x, m_startPoint.m_y);
		canvas.LineTo(m_startPoint.m_x, m_startPoint.m_y + m_height);
		canvas.LineTo(m_startPoint.m_x + m_width, m_startPoint.m_y);
		canvas.MoveTo(m_startPoint.m_x + m_width, m_startPoint.m_y + m_height);
		canvas.LineTo(m_startPoint.m_x - m_width, m_startPoint.m_y);
		canvas.LineTo(m_startPoint.m_x, m_startPoint.m_y - m_height);
	}

	std::string GetShapeName() const final
	{
		return "rectangle";
	}
private:
	Point m_startPoint;
	double m_width;
	double m_height;
};