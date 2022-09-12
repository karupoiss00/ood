#pragma once
#include <iostream>
#include "CountableFlyBehavior.h"

class FlyWithWings : public CountableFlyBehavior
{
public:
	void Fly() override
	{
		std::cout << "I'm flying with wings!!" << std::endl;
		CountableFlyBehavior::Fly();
	}
};