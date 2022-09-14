#pragma once
#include <iostream>
#include <functional>

using FlyStrategy = std::function<void()>;

void FlyNoWay()
{

}

FlyStrategy FlyWithWings()
{
	unsigned flightsCount = 0;

	return [flightsCount]() mutable -> void
	{
		flightsCount++;
		std::cout << "I'm flying with wings!!" << std::endl;
		std::cout << "Flights count = " << flightsCount << std::endl;
	};
}