#pragma once
#include <string>
#include "IShapeStrategy.h"

namespace shapes
{
	class Shape
	{
	public:
		Shape(std::string id, gfx::Color color, std::unique_ptr<IShapeStrategy> strategy)
			: m_id(id), m_color(color), m_shapeStrategy(move(strategy))
		{};

		std::string GetShapeName() const
		{
			return m_shapeStrategy->GetShapeName();
		}

		std::string GetShapeInfo() const
		{
			return m_color + " " + m_shapeStrategy->GetShapeInfo();
		}

		void Move(double dx, double dy)
		{
			m_shapeStrategy->Move(dx, dy);
		}

		void SetShapeStrategy(std::unique_ptr<IShapeStrategy> strategy)
		{
			m_shapeStrategy = move(strategy);
		}

		void SetColor(gfx::Color const& color)
		{
			m_color = color;
		}

		gfx::Color GetColor() const
		{
			return m_color;
		}

		std::string const& GetId() const
		{
			return m_id;
		}

		void Draw(gfx::ICanvas& canvas) const
		{
			canvas.SetColor(m_color);
			m_shapeStrategy->Draw(canvas);
		}
	private:
		std::unique_ptr<IShapeStrategy> m_shapeStrategy;
		gfx::Color m_color;
		std::string m_id;
	};
}