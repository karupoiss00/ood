#include "BaseStyle.h"

using namespace std;

std::optional<bool> CBaseStyle::IsEnabled() const
{
	return m_isEnabled;
}

void CBaseStyle::Enable(bool enable)
{
	m_isEnabled = enable;
}