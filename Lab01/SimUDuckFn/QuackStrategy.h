#pragma once
#include <iostream>
#include <functional>

using QuackStrategy = std::function<void()>;

void MuteQuack()
{

}

void QuackImpl()
{
	std::cout << "Quack Quack!!!" << std::endl;
}

void Squeak()
{
	std::cout << "Squeek!!!" << std::endl;
}