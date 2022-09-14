#pragma once
#include "Duck.h"
#include "FlyStrategy.h"
#include "QuackStrategy.h"
#include "DanceStrategy.h"

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(FlyWithWings(), QuackImpl, DanceMinuet)
	{
	}
	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}
};