#pragma once
#include <functional>
#include <optional>

#include "CompositeStyle.h"
#include "BaseStyle.h"
#include "ColorStyle.h"

using ColorStyleCallback = std::function<void(CColorStyle& style, unsigned index)>;
using ColorStyleEnumerator = std::function<void(const ColorStyleCallback& callback)>;

class CCompositeColorStyle : public CColorStyle, public CCompositeStyle<CColorStyle>
{
public:
	CCompositeColorStyle(const ColorStyleEnumerator& enumerator)
		: CCompositeStyle(enumerator)
		, CColorStyle(false)
	{
	}

	std::optional<RGBAColor> GetColor() const;
	void SetColor(RGBAColor color);
};