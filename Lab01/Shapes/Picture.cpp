#include "Picture.h"

using namespace std;
using namespace shapes;
using namespace gfx;

void Picture::MovePicture(double dx, double dy)
{
	for (auto& shape : m_shapesList)
	{
		shape->Move(dx, dy);
	}
}

void Picture::AddShape(string const& id, Color color, unique_ptr<IShapeStrategy> strategy)
{
	auto it = m_shapesMap.find(id);

	if (it != m_shapesMap.end())
	{
		throw std::exception("shape with this id already exist");
	}

	auto shape = make_shared<Shape>(Shape(id, color, move(strategy)));

	m_shapesMap.insert({ id, shape });
	m_shapesList.push_back(shape);
}

void Picture::DeleteShape(string const& id)
{
	m_shapesList.remove(GetShapeById(id));
	m_shapesMap.erase(id);
}

vector<string> Picture::List()
{
	vector<string> result;

	unsigned counter = 1;

	for (auto& shape : m_shapesList)
	{
		result.push_back
		(
			to_string(counter) + " " + shape->GetShapeName() + " " + shape->GetId() + " " + shape->GetShapeInfo()
		);
		counter++;
	}

	return result;
}

void Picture::Draw(ICanvas& canvas)
{
	for (auto const& shape: m_shapesList)
	{
		shape->Draw(canvas);
	}
}

shared_ptr<Shape> Picture::GetShapeById(string const& id)
{
	auto it = m_shapesMap.find(id);

	if (it == m_shapesMap.end())
	{
		throw std::exception("shape with this id is not exist");
	}
	return it->second;
}
