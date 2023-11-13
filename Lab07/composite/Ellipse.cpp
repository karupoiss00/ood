#include "Ellipse.h"

using namespace std;

CEllipse::CEllipse(double cx, double cy, double rx, double ry, shared_ptr<CLineStyle> const& outlineStyle, shared_ptr<CColorStyle> const& fillStyle)
	: CShape(outlineStyle, fillStyle)
	, m_cx(cx)
	, m_cy(cy)
	, m_rx(rx)
	, m_ry(ry)
{
}

CEllipse::CEllipse(const RectD& rect, shared_ptr<CLineStyle> const& outlineStyle, shared_ptr<CColorStyle> const& fillStyle)
	: CShape(outlineStyle, fillStyle)
	, m_cx(rect.left + rect.width * 0.5)
	, m_cy(rect.top + rect.height * 0.5)
	, m_rx(rect.width * 0.5)
	, m_ry(rect.height * 0.5)
{
}

RectD CEllipse::GetFrameImpl()
{
	return {
		m_cx - m_rx,
		m_cy - m_ry,
		m_rx * 2,
		m_ry * 2,
	};
}

void CEllipse::SetFrameImpl(double offsetLeft, double offsetTop, double scaleWidth, double scaleHeight)
{
	auto newLeft = m_cx - m_rx + offsetLeft;
	auto newTop = m_cy - m_ry + offsetTop;
	auto newWidth = m_rx * 2 * scaleWidth;
	auto newHeight = m_ry * 2 * scaleHeight;
	m_rx = newWidth / 2;
	m_ry = newHeight / 2;
	m_cx = newLeft + m_rx;
	m_cy = newTop + m_ry;
}

void CEllipse::DrawImpl(ICanvas& canvas) const
{
	canvas.DrawEllipse(m_cx - m_rx, m_cy - m_ry, m_rx * 2, m_ry * 2);
}