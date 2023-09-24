#pragma once
#include <array>
#include "Point.h"

class TextStrategy : public IShapeStrategy
{
public:
	TextStrategy(Point startPoint, double fontSize, std::string&& text)
		: m_topLeft(startPoint),
		m_fontSize(fontSize),
		m_text(text)
	{}

	virtual std::string GetShapeInfo() const final
	{
		return std::to_string(m_topLeft.m_x)
			+ " " + std::to_string(m_topLeft.m_y)
			+ " " + std::to_string(m_fontSize)
			+ " " + m_text;
	}

	virtual void Move(double dx, double dy) final
	{
		m_topLeft.m_x += dx;
		m_topLeft.m_y += dy;
	}

	virtual void Draw(gfx::ICanvas& canvas) const final
	{
		canvas.DrawText(m_topLeft.m_x, m_topLeft.m_y, m_fontSize, m_text);
	}

	virtual std::string GetShapeName() const final
	{
		return "text";
	}
private:
	Point m_topLeft;
	double m_fontSize;
	std::string m_text;
};