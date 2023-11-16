#include "ShapeGroup.h"

using namespace std;

CShapeGroup::CShapeGroup()
	: m_outlineStyle(make_shared<CCompositeLineStyle>(bind(&CShapeGroup::EnumerateOutlineStyles, this, placeholders::_1)))
	, m_fillStyle(make_shared<CCompositeColorStyle>(bind(&CShapeGroup::EnumerateFillStyles, this, placeholders::_1)))
{

}

void CShapeGroup::Draw(ICanvas& canvas) const
{
	for (auto& shape : m_shapes.Get())
	{
		shape->Draw(canvas);
	}
}

RectD CShapeGroup::GetFrame()
{
	auto shapes = m_shapes.Get();
	
	if (shapes.empty())
	{
		return { 0, 0, 0, 0 };
	}

	auto leftTopX = numeric_limits<double>::max();
	auto leftTopY = numeric_limits<double>::max();
	auto rightBottomX = numeric_limits<double>::min();
	auto rightBottomY = numeric_limits<double>::min();

	for (auto& shape : shapes)
	{
		auto group = shape->GetGroup();
		if (group && group->GetShapesCount() == 0)
		{
			// [поправлено] пустые группы не вли€ют на позицию результурющего фрейма
			continue;
		}

		auto shapeFrame = shape->GetFrame();

		auto shapeLeftTopX = shapeFrame.left;
		auto shapeLeftTopY = shapeFrame.top;
		auto shapeRightBottomX = shapeFrame.left + shapeFrame.width;
		auto shapeRightBottomY = shapeFrame.top + shapeFrame.height;

		leftTopX = shapeLeftTopX < leftTopX ? shapeLeftTopX : leftTopX;
		leftTopY = shapeLeftTopY < leftTopY ? shapeLeftTopY : leftTopY;
		rightBottomX = shapeRightBottomX > rightBottomX ? shapeRightBottomX : rightBottomX;
		rightBottomY = shapeRightBottomY > rightBottomY ? shapeRightBottomY : rightBottomY;
	}

	return { leftTopX, leftTopY, rightBottomX - leftTopX, rightBottomY - leftTopY };
}

void CShapeGroup::SetFrame(const RectD& rect)
{
	auto shapes = m_shapes.Get();

	if (shapes.empty())
	{
		return;
	}

	auto groupFrame = GetFrame();

	auto scaleWidth = rect.width / groupFrame.width;
	auto scaleHeight = rect.height / groupFrame.height;

	for (auto& shape : shapes)
	{
		auto shapeFrame = shape->GetFrame();

		auto shapeLeftInGroupFrame = shapeFrame.left - groupFrame.left;
		auto shapeLeftDueScaling = shapeLeftInGroupFrame * scaleWidth;

		auto shapeTopInGroupFrame = shapeFrame.top - groupFrame.top;
		auto shapeTopDueScaling = shapeTopInGroupFrame * scaleHeight;

		shape->SetFrame({
			rect.left + shapeLeftDueScaling,
			rect.top + shapeTopDueScaling,
			shapeFrame.width * scaleWidth,
			shapeFrame.height * scaleHeight,
		});
	}
}

std::shared_ptr<CLineStyle> CShapeGroup::GetOutlineStyle()
{
	return m_outlineStyle;
}

std::shared_ptr<const CLineStyle> CShapeGroup::GetOutlineStyle() const
{
	return m_outlineStyle;
}

std::shared_ptr<CColorStyle> CShapeGroup::GetFillStyle()
{
	return m_fillStyle;
}

std::shared_ptr<const CColorStyle> CShapeGroup::GetFillStyle() const
{
	return m_fillStyle;
}

std::shared_ptr<IShapeGroup> CShapeGroup::GetGroup()
{
	return shared_from_this();
}

// [поправлено] наследоватьс€ от shared_pointer_from_this
std::shared_ptr<const IShapeGroup> CShapeGroup::GetGroup() const
{
	return shared_from_this();
}

size_t CShapeGroup::GetShapesCount() const
{
	return m_shapes.GetShapesCount();
}

shared_ptr<IShape> CShapeGroup::GetShapeAtIndex(size_t index) const
{
	return m_shapes.GetShapeAtIndex(index);
}

void CShapeGroup::InsertShape(const std::shared_ptr<IShape>& shape, size_t position)
{
	m_shapes.InsertShape(shape, position);
}

void CShapeGroup::RemoveShapeAtIndex(size_t index)
{
	m_shapes.RemoveShapeAtIndex(index);
}

void CShapeGroup::EnumerateOutlineStyles(const LineStyleCallback& callback)
{
	unsigned index = 0;
	for (auto& shape : m_shapes.Get())
	{
		callback(*shape->GetOutlineStyle(), index);
		index++;
	}
}

void CShapeGroup::EnumerateFillStyles(const ColorStyleCallback& callback)
{
	unsigned index = 0;
	for (auto& shape : m_shapes.Get())
	{
		callback(*shape->GetFillStyle(), index);
		index++;
	}
}