#pragma once
#include "ISlide.h"
#include "Shape.h"
#include "Shapes.h"

class CSlide : public ISlide
{
public:
	double GetWidth() const;
	double GetHeight() const;

	size_t GetShapesCount() const;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index);
	void InsertShape(const std::shared_ptr<CShape>& shape, size_t position = std::numeric_limits<size_t>::max());
	void RemoveShapeAtIndex(size_t index);

	RGBAColor GetBackgroundColor() const;
	void SetBackgroundColor(RGBAColor color);
	IShapes& GetShapes();
	void Draw(ICanvas& canvas) const;
private:
	void DrawSelf(ICanvas& canvas) const;

	double m_width = 1024;
	double m_height = 768;

	CShapes m_shapes;

	RGBAColor m_backgroundColor;
};