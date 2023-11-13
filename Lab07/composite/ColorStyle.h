#pragma once
#include <optional>
#include "BaseStyle.h"

class CColorStyle : public CBaseStyle
{
public:
	CColorStyle() = default;
	CColorStyle(std::optional<RGBAColor> color)
		: m_color(color)
	{}

	virtual std::optional<RGBAColor> GetColor() const;
	virtual void SetColor(RGBAColor color);

private:
	std::optional<RGBAColor> m_color;
};