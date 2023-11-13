#pragma once
#include <vector>
#include "IShapes.h"

class CShapes : public IShapes
{
public:
	size_t GetShapesCount() const override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const override;

	void InsertShape(const std::shared_ptr<IShape>& shape, size_t position) override;
	void RemoveShapeAtIndex(size_t index) override;

protected:
	std::vector<std::shared_ptr<IShape>>& GetShapes();
	const std::vector<std::shared_ptr<IShape>>& GetShapes() const;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};