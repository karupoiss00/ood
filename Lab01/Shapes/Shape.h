#pragma once
#include <string>
#include "IShapeStrategy.h"

class Shape
{
public:
	Shape(IShapeStrategy& strategy)
		: m_shapeStrategy(strategy)
	{};
	
	std::string GetShapeInfo() const
	{
		return m_shapeStrategy.GetShapeInfo();
	}

	void Move(double dx, double dy)
	{
		m_shapeStrategy.Move(dx, dy);
	}

	void Draw(ICanvas& canvas)
	{
		m_shapeStrategy.Draw(canvas);
	}

	void SetColor(Color const& color)
	{
		m_shapeStrategy.SetColor(color);
	}

	void SetShapeStrategy(IShapeStrategy& strategy)
	{
		m_shapeStrategy = strategy;
	}

private:
	IShapeStrategy& m_shapeStrategy;
};