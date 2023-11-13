#pragma once
#include "ICanvas.h"
#include "IShape.h"
#include "LineStyle.h"
#include "ColorStyle.h"

class CShape : public IShape
{
public:
	CShape(std::shared_ptr<CLineStyle> const& outlineStyle, std::shared_ptr<CColorStyle> const& fillStyle);

	RectD GetFrame() override;
	void SetFrame(const RectD& rect) override;

	std::shared_ptr<CLineStyle> GetOutlineStyle() override;
	std::shared_ptr<const CLineStyle> GetOutlineStyle() const override;

	std::shared_ptr<CColorStyle> GetFillStyle() override;
	std::shared_ptr<const CColorStyle> GetFillStyle() const override;

	std::shared_ptr<IShapeGroup> GetGroup() override;
	std::shared_ptr<const IShapeGroup> GetGroup() const override;

	void Draw(ICanvas& canvas) const;

protected:
	virtual RectD GetFrameImpl() = 0;
	virtual void SetFrameImpl(double offsetLeft, double offsetTop, double scaleWidth, double scaleHeight) = 0;
	virtual void DrawImpl(ICanvas& canvas) const = 0;

private:
	std::shared_ptr<CLineStyle> m_outlineStyle;
	std::shared_ptr<CColorStyle> m_fillStyle;
};