#pragma once
#include <array>
#include "LineStyle.h"
#include "ColorStyle.h"
#include "Shape.h"

class CTriangle : public CShape
{
public:
	CTriangle(std::array<PointD, 3> vertexes, std::shared_ptr<CLineStyle> const& outlineStyle, std::shared_ptr<CColorStyle> const& fillStyle);

protected:
	RectD GetFrameImpl() override;
	void SetFrameImpl(double offsetLeft, double offsetTop, double scaleWidth, double scaleHeight) override;
	void DrawImpl(ICanvas& canvas) const override;

private:
	double m_left;
	double m_top;
	double m_width;
	double m_height;
	std::array<PointD, 3> m_vertexes;
};