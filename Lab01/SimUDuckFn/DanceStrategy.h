#pragma once
#include <iostream>
#include <functional>

using DanceStrategy = std::function<void()>;

void DanceNoWay()
{

}

void DanceWaltz()
{
	std::cout << "I'm dancing waltz" << std::endl;
}

void DanceMinuet()
{
	std::cout << "I'm dancing minuet" << std::endl;
}