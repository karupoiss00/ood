#pragma once
#include <array>
#include "ShapeStrategy.h"
#include "Point.h"

class TextStrategy : public ShapeStrategy
{
public:
	TextStrategy(Point startPoint, double fontSize, std::string&& text)
		: m_startPoint(startPoint),
		m_fontSize(fontSize),
		m_text(text)
	{}

	virtual std::string GetShapeInfo() const final
	{
		return ShapeStrategy::GetShapeInfo()
			+ " " + std::to_string(m_startPoint.m_x)
			+ " " + std::to_string(m_startPoint.m_y)
			+ " " + std::to_string(m_fontSize)
			+ " " + m_text;
	}

	virtual void Move(double dx, double dy) final
	{
		m_startPoint.m_x += dx;
		m_startPoint.m_y += dy;
	}

	virtual void Draw(sfx::ICanvas& canvas) const final
	{
		ShapeStrategy::Draw(canvas);

		canvas.DrawText(m_startPoint.m_x, m_startPoint.m_y, m_text);
	}

	virtual std::string GetShapeName() const final
	{
		return "text";
	}
private:
	Point m_startPoint;
	double m_fontSize;
	std::string m_text;
};