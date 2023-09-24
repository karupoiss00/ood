#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <list>
#include <memory>
#include "Shape.h"

namespace shapes
{
	class Picture
	{
	public:
		void MovePicture(double dx, double dy);
		void AddShape(std::string const& id, gfx::Color color, std::unique_ptr<IShapeStrategy> strategy);
		void DeleteShape(std::string const& id);
		void Draw(gfx::ICanvas& canvas);

		std::shared_ptr<Shape> GetShapeById(std::string const& id);

		std::vector<std::string> List();
	private:
		

		std::unordered_map<std::string, std::shared_ptr<Shape>> m_shapesMap;
		std::list<std::shared_ptr<Shape>> m_shapesList;
	};
}