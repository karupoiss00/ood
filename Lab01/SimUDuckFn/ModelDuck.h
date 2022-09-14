#pragma once
#include "Duck.h"
#include "FlyStrategy.h"
#include "QuackStrategy.h"
#include "DanceStrategy.h"
class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(FlyNoWay, QuackImpl, DanceNoWay)
	{
	}
	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}
};