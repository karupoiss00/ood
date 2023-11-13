#pragma once
#include <optional>
#include "ColorStyle.h"
#include "BaseStyle.h"

class CLineStyle : public CBaseStyle
{
public:
	CLineStyle(unsigned width, std::optional<RGBAColor> color = std::nullopt)
		: m_colorStyle(CColorStyle(color))
		, m_width(width)
	{
	}

	virtual std::optional<RGBAColor> GetColor() const;
	virtual void SetColor(RGBAColor color);

	virtual unsigned GetWidth() const;
	virtual void SetWidth(unsigned color);

private:
	CColorStyle m_colorStyle;
	unsigned m_width;
};