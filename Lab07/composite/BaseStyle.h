#pragma once
#include <optional>
#include "IStyle.h"

class CBaseStyle : public IStyle
{
public:
	CBaseStyle()
		: m_isEnabled(std::nullopt)
	{};
	CBaseStyle(bool enabled)
		: m_isEnabled(enabled)
	{}

	std::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

private:
	std::optional<bool> m_isEnabled;
};