#pragma once
#include "Duck.h"
#include "FlyStrategy.h"
#include "QuackStrategy.h"
#include "DanceStrategy.h"

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(FlyNoWay, Squeak, DanceNoWay)
	{
	}
	void Display() const override
	{
		std::cout << "I'm rubber duck" << std::endl;
	}
};