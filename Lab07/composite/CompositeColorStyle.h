#pragma once
#include <functional>
#include <optional>

#include "BaseStyle.h"
#include "ColorStyle.h"

using ColorStyleCallback = std::function<void(CColorStyle& style)>;
using ColorStyleEnumerator = std::function<void(const ColorStyleCallback& callback)>;

class CCompositeColorStyle : public CColorStyle
{
public:
	CCompositeColorStyle(const ColorStyleEnumerator& enumerator)
		: m_enumerator(enumerator)
	{
	}

	std::optional<RGBAColor> GetColor() const;
	void SetColor(RGBAColor color);

protected:
	template <typename T>
	T GetStyleValue(std::function<T(CColorStyle& style)> getValueFn) const;

private:
	ColorStyleEnumerator m_enumerator;
};