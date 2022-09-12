#pragma once

struct IFlyBehavior
{
	virtual ~IFlyBehavior() {};
	virtual unsigned GetFlightsCount() = 0;
	virtual void Fly() = 0;
};