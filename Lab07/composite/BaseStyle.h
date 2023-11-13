#pragma once
#include <optional>
#include "IStyle.h"

class CBaseStyle : public IStyle
{
public:
	CBaseStyle()
		: m_isEnabled(true)
	{};
	CBaseStyle(bool enabled)
		: m_isEnabled(enabled)
	{}

	bool IsEnabled() const override;
	void Enable(bool enable) override;

private:
	bool m_isEnabled;
};