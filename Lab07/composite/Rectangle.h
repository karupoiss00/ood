#pragma once
#include "Shape.h"

class CRectangle : public CShape
{
public:
	CRectangle(const RectD& rect, std::shared_ptr<CLineStyle> const& outlineStyle, std::shared_ptr<CColorStyle> const& fillStyle);

protected:
	RectD GetFrameImpl() override;
	void SetFrameImpl(double offsetLeft, double offsetTop, double scaleWidth, double scaleHeight) override;
	void DrawImpl(ICanvas& canvas) const override;

private:
	double m_left;
	double m_top;
	double m_width;
	double m_height;
};