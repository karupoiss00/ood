#include <stdexcept>
#include "Shapes.h"

using namespace std;

size_t CShapes::GetShapesCount() const
{
	return m_shapes.size();
}

shared_ptr<IShape> CShapes::GetShapeAtIndex(size_t index) const
{
	return m_shapes.at(index);
}

void CShapes::InsertShape(const shared_ptr<IShape>& shape, size_t position)
{
	auto it = position > m_shapes.size() ? m_shapes.end() : m_shapes.begin() + position;
	m_shapes.insert(it, shape);
}

void CShapes::RemoveShapeAtIndex(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw out_of_range("Invalid remove index");
	}

	m_shapes.erase(m_shapes.begin() + index);
}

vector<shared_ptr<IShape>>& CShapes::GetShapes()
{
	return m_shapes;
}

const std::vector<std::shared_ptr<IShape>>& CShapes::GetShapes() const
{
	return m_shapes;
}
