#pragma once
#pragma once
#include "IFlyBehavior.h"

class FlyNoWay : public IFlyBehavior
{
public:
	void Fly() override {}
	unsigned GetFlightsCount() override
	{
		return 0;
	}
};