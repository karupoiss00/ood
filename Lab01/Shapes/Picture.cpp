#include "Picture.h"

using namespace std;
using namespace shapes;
using namespace sfx;

void Picture::MovePicture(double dx, double dy)
{
	for (auto& [key, shape] : m_shapes)
	{
		shape.Move(dx, dy);
	}
}

void Picture::AddShape(string const& id, unique_ptr<IShapeStrategy> strategy)
{
	auto it = m_shapes.find(id);

	if (it != m_shapes.end())
	{
		throw std::exception("shape with this id already exist");
	}

	m_shapes.insert({ id, Shape(move(strategy)) });
}

void Picture::ChangeShape(string const& id, unique_ptr<IShapeStrategy> strategy)
{
	Shape& shape = GetShapeById(id);
	strategy->SetColor(shape.GetColor());
	shape.SetShapeStrategy(move(strategy));
}

void Picture::ChangeColor(string const& id, Color color)
{
	GetShapeById(id).SetColor(color);
}

void Picture::MoveShape(string const& id, double dx, double dy)
{
	GetShapeById(id).Move(dx, dy);
}

void Picture::DeleteShape(string const& id)
{
	m_shapes.erase(id);
}

vector<string> Picture::List()
{
	vector<string> result;

	unsigned counter = 1;

	for (auto& [key, shape] : m_shapes)
	{
		result.push_back
		(
			to_string(counter) + " " + shape.GetShapeName() + " " + key + " " + shape.GetShapeInfo()
		);
		counter++;
	}

	return result;
}

void Picture::Draw(ICanvas& canvas)
{
	for (auto const& [key, shape] : m_shapes)
	{
		shape.Draw(canvas);
	}
}

void Picture::DrawShape(string const& id, ICanvas& canvas)
{
	GetShapeById(id).Draw(canvas);
}

Shape& Picture::GetShapeById(string const& id)
{
	auto it = m_shapes.find(id);

	if (it == m_shapes.end())
	{
		throw std::exception("shape with this id is not exist");
	}
	return it->second;
}
