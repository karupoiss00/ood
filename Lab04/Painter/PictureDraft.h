#pragma once
#include <memory>
#include <vector>
#include <boost/iterator/indirect_iterator.hpp>
#include "Shape.h"

class CPictureDraft
{

public:
	using Storage = std::vector<ShapePointer>;
	using ConstIterator = boost::indirect_iterator<Storage::const_iterator, CShape const&>;

	CPictureDraft();

	bool IsEmpty() const;

	ConstIterator begin() const;
	ConstIterator end() const;

	void AddShape(ShapePointer&& shape);

	CPictureDraft(CPictureDraft&&) = default;
	CPictureDraft& operator=(CPictureDraft&&) = default;

	CPictureDraft(const CPictureDraft&) = delete;
	CPictureDraft& operator=(const CPictureDraft&) = delete;
private:
	Storage m_shapes;
};

inline CPictureDraft::ConstIterator begin(const CPictureDraft& draft)
{
	return draft.begin();
}

inline CPictureDraft::ConstIterator end(const CPictureDraft& draft)
{
	return draft.end();
}
