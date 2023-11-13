#pragma once
#include "Shape.h"

class CEllipse : public CShape
{
public:
	CEllipse(double cx, double cy, double rx, double ry, std::shared_ptr<CLineStyle> const& outlineStyle, std::shared_ptr<CColorStyle> const& fillStyle);
	CEllipse(const RectD& rect, std::shared_ptr<CLineStyle> const& outlineStyle, std::shared_ptr<CColorStyle> const& fillStyle);

protected:
	RectD GetFrameImpl() override;
	void SetFrameImpl(double offsetLeft, double offsetTop, double scaleWidth, double scaleHeight) override;
	void DrawImpl(ICanvas& canvas) const override;

private:
	double m_cx;
	double m_cy;
	double m_rx;
	double m_ry;
};