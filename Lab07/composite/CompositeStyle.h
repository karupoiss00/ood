#pragma once
#include <functional>
#include <optional>
#include <vector>

template <typename STYLE>
using StyleCallback = std::function<void(STYLE& style)>;

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
		std::vector<VALUE> values;

		m_enumerator([&](STYLE& style) {
			values.push_back(getValueFn(style));
		});

		auto valuesIsNotEmptyAndEqual = [&values]() {
			return !values.empty() && equal(values.begin() + 1, values.end(), values.begin());
		};

		return valuesIsNotEmptyAndEqual() ? values[0] : std::nullopt;
	}

	StyleEnumerator<STYLE> m_enumerator;
};