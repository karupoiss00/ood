#pragma once
#include <string>
#include "IShapeStrategy.h"

namespace shapes
{
	class Shape
	{
	public:
		Shape(std::unique_ptr<IShapeStrategy> strategy)
			: m_shapeStrategy(move(strategy))
		{};

		std::string GetShapeName() const
		{
			return m_shapeStrategy->GetShapeName();
		}

		std::string GetShapeInfo() const
		{
			return m_shapeStrategy->GetShapeInfo();
		}

		void Move(double dx, double dy)
		{
			m_shapeStrategy->Move(dx, dy);
		}

		void Draw(sfx::ICanvas& canvas) const
		{
			m_shapeStrategy->Draw(canvas);
		}

		void SetColor(sfx::Color const& color)
		{
			m_shapeStrategy->SetColor(color);
		}

		void SetShapeStrategy(std::unique_ptr<IShapeStrategy> strategy)
		{
			m_shapeStrategy = move(strategy);
		}

		sfx::Color GetColor() const
		{
			return m_shapeStrategy->GetColor();
		}

	private:
		std::unique_ptr<IShapeStrategy> m_shapeStrategy;
	};
}