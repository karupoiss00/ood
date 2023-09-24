#pragma once
#include "Point.h"

class RectangleStrategy : public IShapeStrategy
{
public:
	RectangleStrategy(Point startPoint, double width, double height)
		: m_topLeft(startPoint), 
		m_width(width), 
		m_height(height)
	{}

	std::string GetShapeInfo() const final
	{
		return std::to_string(m_topLeft.m_x)
			+ " " + std::to_string(m_topLeft.m_y)
			+ " " + std::to_string(m_width)
			+ " " + std::to_string(m_height);
	}

	void Move(double dx, double dy) final
	{
		m_topLeft.m_x += dx;
		m_topLeft.m_y += dy;
	}

	void Draw(gfx::ICanvas& canvas) const final
	{
		canvas.MoveTo(m_topLeft.m_x, m_topLeft.m_y);
		canvas.LineTo(m_topLeft.m_x, m_topLeft.m_y + m_height);
		canvas.LineTo(m_topLeft.m_x + m_width, m_topLeft.m_y);

		canvas.MoveTo(m_topLeft.m_x + m_width, m_topLeft.m_y + m_height);
		canvas.LineTo(m_topLeft.m_x, m_topLeft.m_y + m_height);
		canvas.LineTo(m_topLeft.m_x + m_width, m_topLeft.m_y);
	}

	std::string GetShapeName() const final
	{
		return "rectangle";
	}
private:
	Point m_topLeft;
	double m_width;
	double m_height;
};