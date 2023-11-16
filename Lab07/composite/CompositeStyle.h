#pragma once
#include <functional>
#include <optional>
#include <vector>

template <typename STYLE>
using StyleCallback = std::function<void(STYLE& style, unsigned index)>;

template <typename STYLE>
using StyleEnumerator = std::function<void(const StyleCallback<STYLE>& callback)>;



template <typename STYLE>
class CCompositeStyle
{
public:
	CCompositeStyle(const StyleEnumerator<STYLE>& enumerator)
		: m_enumerator(enumerator)
	{
	}

protected:
	template <typename VALUE>
	VALUE GetStyleValue(std::function<VALUE(STYLE& style)> getValueFn) const
	{
		// [поправлено] O(1) по памяти
		VALUE firstStyleValue = std::nullopt;
		bool allStylesEqual = true;

		m_enumerator([&](STYLE& style, unsigned index) {
			if (!allStylesEqual)
			{
				return;
			}

			auto val = getValueFn(style);
			if (index == 0)
			{
				firstStyleValue = val;
				return;
			}
			
			allStylesEqual = allStylesEqual && firstStyleValue == val;		
		});

		return allStylesEqual ? firstStyleValue : std::nullopt;
	}

	StyleEnumerator<STYLE> m_enumerator;
};