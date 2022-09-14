#pragma once
#include "Duck.h"
#include "FlyStrategy.h"
#include "QuackStrategy.h"
#include "DanceStrategy.h"

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWings(), QuackImpl, DanceWaltz)
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck" << std::endl;
	}
};