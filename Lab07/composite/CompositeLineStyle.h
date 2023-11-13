#pragma once
#include <functional>
#include <optional>

#include "BaseStyle.h"
#include "CompositeColorStyle.h"
#include "LineStyle.h"

using LineStyleCallback = std::function<void(CLineStyle& style)>;
using LineStyleEnumerator = std::function<void(const LineStyleCallback& callback)>;

class CCompositeLineStyle : public CLineStyle
{
public:
	CCompositeLineStyle(const LineStyleEnumerator& enumerator)
		: CLineStyle(0)
		, m_enumerator(enumerator)
	{
	}

	std::optional<RGBAColor> GetColor() const;
	void SetColor(RGBAColor color);

	unsigned GetWidth() const;
	void SetWidth(unsigned color);

protected:
	template <typename T>
	T GetStyleValue(std::function<T(CLineStyle& style)> getValueFn) const;

private:
	LineStyleEnumerator m_enumerator;
};