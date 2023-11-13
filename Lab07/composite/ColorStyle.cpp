#include "ColorStyle.h"

std::optional<RGBAColor> CColorStyle::GetColor() const
{
	return m_color;
}

void CColorStyle::SetColor(RGBAColor color)
{
	m_color = color;
}