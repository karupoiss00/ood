#pragma once
#include <functional>

#include "CompositeColorStyle.h"
#include "CompositeLineStyle.h"
#include "IShapeGroup.h"
#include "Shapes.h"

class CShapeGroup : public IShapeGroup, public CShapes
{	
public:
	CShapeGroup();

	void Draw(ICanvas& canvas) const override;

	RectD GetFrame() override;
	void SetFrame(const RectD& rect) override;

	std::shared_ptr<CLineStyle> GetOutlineStyle() override;
	std::shared_ptr<const CLineStyle> GetOutlineStyle() const override;

	std::shared_ptr<CColorStyle> GetFillStyle() override;
	std::shared_ptr<const CColorStyle> GetFillStyle() const override;

	std::shared_ptr<IShapeGroup> GetGroup() override;
	std::shared_ptr<const IShapeGroup> GetGroup() const override;

	size_t GetShapesCount() const override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const override;

	void InsertShape(const std::shared_ptr<IShape>& shape, size_t position = std::numeric_limits<size_t>::max()) override;
	void RemoveShapeAtIndex(size_t index) override;

private:
	void EnumerateOutlineStyles(const LineStyleCallback& callback);
	void EnumerateFillStyles(const ColorStyleCallback& callback);

	std::shared_ptr<CLineStyle> m_outlineStyle;
	std::shared_ptr<CColorStyle> m_fillStyle;
};