#pragma once
#include <string>
#include "ICanvas.h"
#include "IShapeStrategy.h"

class ShapeStrategy : public IShapeStrategy
{
public:
	ShapeStrategy(Color color)
		: m_color(color), m_id("TODO: unique id")
	{}

	virtual std::string GetShapeInfo() const
	{
		return GetShapeName() + " " + m_id + " " + m_color.ToHex();
	}

	virtual void SetColor(Color const& color) final
	{
		m_color = color;
	}

	virtual void Draw(ICanvas& canvas)
	{
		canvas.SetColor(m_color);
	}

	virtual std::string GetShapeName() const = 0;
private:
	std::string m_id;
	Color m_color;
};