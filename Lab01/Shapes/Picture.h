#pragma once
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Shape.h"

namespace shapes
{
	class Picture
	{
	public:
		void MovePicture(double dx, double dy);
		void AddShape(std::string const& id, std::unique_ptr<IShapeStrategy> strategy);
		void ChangeShape(std::string const& id, std::unique_ptr<IShapeStrategy> strategy);
		void ChangeColor(std::string const& id, sfx::Color color);
		void MoveShape(std::string const& id, double dx, double dy);
		void DeleteShape(std::string const& id);
		void DrawShape(std::string const& id, sfx::ICanvas& canvas);
		void Draw(sfx::ICanvas& canvas);

		std::vector<std::string> List();
	private:
		Shape& GetShapeById(std::string const& id);

		std::map<std::string, Shape> m_shapes;
	};
}