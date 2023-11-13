#include "Slide.h"

void CSlide::Draw(ICanvas& canvas) const
{
	DrawSelf(canvas);

	for (size_t i = 0; i < m_shapes.GetShapesCount(); ++i)
	{
		auto shape = m_shapes.GetShapeAtIndex(i);
		shape->Draw(canvas);
	}
}

double CSlide::GetWidth() const
{
	return m_width;
}

double CSlide::GetHeight() const
{
	return m_height;
}

IShapes& CSlide::GetShapes()
{
	return m_shapes;
}

void CSlide::DrawSelf(ICanvas& canvas) const {
	canvas.SetLineColor(0);
	canvas.MoveTo(0, 0);
	canvas.LineTo(m_width, 0);
	canvas.MoveTo(m_width, 0);
	canvas.LineTo(m_width, m_height);
	canvas.MoveTo(m_width, m_height);
	canvas.LineTo(0, m_height);
}

size_t CSlide::GetShapesCount() const
{
	return m_shapes.GetShapesCount();
}

std::shared_ptr<IShape> CSlide::GetShapeAtIndex(size_t index)
{
	return m_shapes.GetShapeAtIndex(index);
}

void CSlide::InsertShape(const std::shared_ptr<CShape>& shape, size_t position)
{
	m_shapes.InsertShape(shape, position);
}

void CSlide::RemoveShapeAtIndex(size_t index)
{
	m_shapes.RemoveShapeAtIndex(index);
}

RGBAColor CSlide::GetBackgroundColor() const
{
	return m_backgroundColor;
}

void CSlide::SetBackgroundColor(RGBAColor color)
{
	m_backgroundColor = color;
}