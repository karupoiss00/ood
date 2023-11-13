#include "BaseStyle.h"

using namespace std;

bool CBaseStyle::IsEnabled() const
{
	return m_isEnabled;
}

void CBaseStyle::Enable(bool enable)
{
	m_isEnabled = enable;
}