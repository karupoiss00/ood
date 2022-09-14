#pragma once
#include <iostream>
#include "IFlyBehavior.h"

class FlyWithWings : public IFlyBehavior
{
public:
	void Fly() override
	{
		m_flightsCount++;
		std::cout << "I'm flying with wings!!" << std::endl;
		std::cout << "Flights count = " << m_flightsCount << std::endl;
	}
private:
	unsigned m_flightsCount;
};