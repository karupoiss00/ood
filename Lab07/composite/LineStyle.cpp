#include "LineStyle.h"

unsigned CLineStyle::GetWidth() const {
	return m_width;
}

void CLineStyle::SetWidth(unsigned width)
{
	m_width = width;
}

std::optional<RGBAColor> CLineStyle::GetColor() const
{
	return m_colorStyle.GetColor();
}

void CLineStyle::SetColor(RGBAColor color)
{
	m_colorStyle.SetColor(color);
}