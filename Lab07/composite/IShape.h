#pragma once
#include <memory>
#include "IDrawable.h"
#include "LineStyle.h"
#include "ColorStyle.h"

class IShapeGroup;

class IShape : public IDrawable
{
public:
	virtual RectD GetFrame() = 0;
	virtual void SetFrame(const RectD& rect) = 0;

	virtual std::shared_ptr<CLineStyle> GetOutlineStyle() = 0;
	virtual std::shared_ptr<const CLineStyle> GetOutlineStyle() const = 0;

	virtual std::shared_ptr<CColorStyle> GetFillStyle() = 0;
	virtual std::shared_ptr<const CColorStyle> GetFillStyle() const = 0;

	virtual std::shared_ptr<IShapeGroup> GetGroup() = 0;
	virtual std::shared_ptr<const IShapeGroup> GetGroup() const = 0;

	virtual ~IShape() = default;
};