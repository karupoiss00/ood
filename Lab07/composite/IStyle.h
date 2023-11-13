#pragma once
#include "CommonTypes.h"

class IStyle
{
public:
	virtual bool IsEnabled() const = 0;
	virtual void Enable(bool enable) = 0;

	virtual ~IStyle() = default;
};