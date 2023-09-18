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

	void SetColor(sfx::Color const& color) override
	{
		m_color = color;
	}

	sfx::Color GetColor() const override
	{
		return m_color;
	}

	void Draw(sfx::ICanvas& canvas) const override
	{
		canvas.SetColor(m_color);
	}
	
private:
	sfx::Color m_color;
};