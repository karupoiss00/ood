#include "CompositeColorStyle.h"

using namespace std;

optional<RGBAColor> CCompositeColorStyle::GetColor() const
{
	return GetStyleValue<optional<RGBAColor>>([](CColorStyle& style) {
		return style.GetColor();
	});
}

void CCompositeColorStyle::SetColor(RGBAColor color)
{
	m_enumerator([color](CColorStyle& style) {
		style.SetColor(color);
	});
}

template <typename T>
T CCompositeColorStyle::GetStyleValue(std::function<T(CColorStyle& style)> getValueFn) const
{
	vector<T> values;

	m_enumerator([&](CColorStyle& style) {
		values.push_back(getValueFn(style));
	});

	auto valuesIsNotEmptyAndEqual = [&values]() {
		return !values.empty() && equal(values.begin() + 1, values.end(), values.begin());
	};

	return valuesIsNotEmptyAndEqual() ? values[0] : nullopt;
}