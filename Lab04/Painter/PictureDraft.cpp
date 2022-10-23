#include "PictureDraft.h"

using namespace std;

CPictureDraft::CPictureDraft()
{
}

bool CPictureDraft::IsEmpty() const
{
	return m_shapes.empty();
}

CPictureDraft::ConstIterator CPictureDraft::begin() const
{
	return m_shapes.begin();
}

CPictureDraft::ConstIterator CPictureDraft::end() const
{
	return m_shapes.end();
}

void CPictureDraft::AddShape(ShapePointer&& shape)
{
	m_shapes.push_back(move(shape));
}
