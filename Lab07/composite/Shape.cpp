#include "Shape.h"

using namespace std;

constexpr RGBAColor DEFAULT_COLOR = 0;

CShape::CShape(shared_ptr<CLineStyle> const& outlineStyle, shared_ptr<CColorStyle> const& fillStyle)
	: m_outlineStyle(outlineStyle)
	, m_fillStyle(fillStyle)
{
}

RectD CShape::GetFrame()
{
	return GetFrameImpl();
}

void CShape::SetFrame(const RectD& rect)
{
	auto oldRect = GetFrame();

	auto offsetLeft = rect.left - oldRect.left;
	auto offsetTop = rect.top - oldRect.top;
	auto scaleWidth = rect.width / oldRect.width;
	auto scaleHeight = rect.height / oldRect.height;

	SetFrameImpl(offsetLeft, offsetTop, scaleWidth, scaleHeight);
}

shared_ptr<CLineStyle> CShape::GetOutlineStyle()
{
	return m_outlineStyle;
}

shared_ptr<const CLineStyle> CShape::GetOutlineStyle() const
{
	return m_outlineStyle;
}

shared_ptr<CColorStyle> CShape::GetFillStyle()
{
	return m_fillStyle;
}

shared_ptr<const CColorStyle> CShape::GetFillStyle() const
{
	return m_fillStyle;
}

shared_ptr<IShapeGroup> CShape::GetGroup()
{
	return nullptr;
}

shared_ptr<const IShapeGroup> CShape::GetGroup() const
{
	return nullptr;
}

void CShape::Draw(ICanvas& canvas) const
{
	auto outlineColor = m_outlineStyle->GetColor();
	auto outlineWidth = m_outlineStyle->GetWidth();
	auto fillColor = m_fillStyle->GetColor();

	if (fillColor.has_value())
	{
		canvas.BeginFill(*fillColor);
	}
	
	auto lineColor = outlineColor.has_value()
		? *outlineColor
		: DEFAULT_COLOR;

	canvas.SetLineColor(lineColor);
	canvas.SetLineWidth(outlineWidth);

	DrawImpl(canvas);

	canvas.EndFill();
}
