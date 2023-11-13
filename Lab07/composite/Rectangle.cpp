#include "Rectangle.h"

using namespace std;

CRectangle::CRectangle(const RectD& rect, shared_ptr<CLineStyle> const& outlineStyle, shared_ptr<CColorStyle> const& fillStyle)
	: CShape(outlineStyle, fillStyle)
	, m_left(rect.left)
	, m_top(rect.top)
	, m_width(rect.width)
	, m_height(rect.height)
{
}

RectD CRectangle::GetFrameImpl()
{
	return { m_left, m_top, m_width, m_height };
}

void CRectangle::SetFrameImpl(double offsetLeft, double offsetTop, double scaleWidth, double scaleHeight)
{
	m_left += offsetLeft;
	m_top += offsetTop;
	m_width *= scaleWidth;
	m_height *= scaleHeight;
}

void CRectangle::DrawImpl(ICanvas& canvas) const
{
	canvas.MoveTo(m_left, m_top);
	canvas.LineTo(m_left + m_width, m_top);

	canvas.MoveTo(m_left + m_width, m_top);
	canvas.LineTo(m_left + m_width, m_top + m_height);

	canvas.MoveTo(m_left + m_width, m_top + m_height);
	canvas.LineTo(m_left, m_top + m_height);

	canvas.MoveTo(m_left, m_top + m_height);
	canvas.LineTo(m_left, m_top);
}
