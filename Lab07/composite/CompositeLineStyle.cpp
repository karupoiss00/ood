#include "CompositeLineStyle.h"

using namespace std;

optional<RGBAColor> CCompositeLineStyle::GetColor() const
{
	return GetStyleValue<optional<RGBAColor>>([](CLineStyle& style) {
		return style.GetColor();
	});
}

void CCompositeLineStyle::SetColor(RGBAColor color)
{
	m_enumerator([color](CLineStyle& style) {
		style.SetColor(color);
	});
}

unsigned CCompositeLineStyle::GetWidth() const
{
	auto value = GetStyleValue<optional<unsigned>>([](CLineStyle& style) {
		return style.GetWidth();
	});

	return value.has_value() ? *value : 0;
}

void CCompositeLineStyle::SetWidth(unsigned width)
{
	m_enumerator([width](CLineStyle& style) {
		style.SetWidth(width);
	});
}

template <typename T>
T CCompositeLineStyle::GetStyleValue(std::function<T(CLineStyle& style)> getValueFn) const
{
	vector<T> values;

	m_enumerator([&](CLineStyle& style) {
		values.push_back(getValueFn(style));
	});

	auto valuesIsNotEmptyAndEqual = [&values]() {
		return !values.empty() && equal(values.begin() + 1, values.end(), values.begin());
	};

	return valuesIsNotEmptyAndEqual() ? values[0] : nullopt;
}