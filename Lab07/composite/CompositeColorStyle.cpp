#include "CompositeColorStyle.h"

using namespace std;

optional<RGBAColor> CCompositeColorStyle::GetColor() const
{
	return GetStyleValue<optional<RGBAColor>>([](CColorStyle& style) {
		return style.GetColor();
	});
}

void CCompositeColorStyle::SetColor(RGBAColor color)
{
	m_enumerator([color](CColorStyle& style, unsigned index) {
		style.SetColor(color);
	});
}