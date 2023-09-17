#pragma once
#include <string>
#include "ICanvas.h"
#include "IShapeStrategy.h"

class ShapeStrategy : public IShapeStrategy
{
public:
	std::string GetShapeInfo() const override
	{
		return m_color.ToHex();
	}

	void SetColor(Color const& color) override
	{
		m_color = color;
	}

	Color GetColor() const override
	{
		return m_color;
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.SetColor(m_color);
	}
	
private:
	Color m_color;
};