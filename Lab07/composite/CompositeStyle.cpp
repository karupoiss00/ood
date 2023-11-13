#include "CompositeStyle.h"


template <typename VALUE_TYPE, typename STYLE_TYPE>
VALUE_TYPE CCompositeStyle::GetStyleValue(std::function<VALUE_TYPE(STYLE_TYPE& style)> getValueFn) const
{
	vector<T> values;

	m_enumerator([&](STYLE_TYPE& style) {
		values.push_back(getValueFn(style));
	});

	auto valuesIsNotEmptyAndEqual = [&values]() {
		return !values.empty() && equal(values.begin() + 1, values.end(), values.begin());
	};

	return valuesIsNotEmptyAndEqual() ? values[0] : nullopt;
}