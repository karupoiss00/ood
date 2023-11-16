#pragma once
#include <functional>
#include <optional>

#include "BaseStyle.h"
#include "CompositeStyle.h"
#include "CompositeColorStyle.h"
#include "LineStyle.h"

using LineStyleCallback = std::function<void(CLineStyle& style, unsigned index)>;
using LineStyleEnumerator = std::function<void(const LineStyleCallback& callback)>;

// заменить наследование композицией
class CCompositeLineStyle : public CLineStyle, public CCompositeStyle<CLineStyle>
{
public:
	CCompositeLineStyle(const LineStyleEnumerator& enumerator)
		: CLineStyle(0)
		, CCompositeStyle(enumerator)
	{
	}

	std::optional<RGBAColor> GetColor() const;
	void SetColor(RGBAColor color);

	unsigned GetWidth() const;
	void SetWidth(unsigned color);
};