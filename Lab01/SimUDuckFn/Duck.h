#pragma once
#include <cassert>
#include <iostream>
#include <vector>
#include "FlyStrategy.h"
#include "QuackStrategy.h"
#include "DanceStrategy.h"

class Duck
{
public:
	Duck(FlyStrategy const& flyBehavior,
		QuackStrategy const& quackBehavior,
		DanceStrategy const& danceBehavior)
		: m_quackBehavior(quackBehavior),
		m_danceBehavior(danceBehavior)
	{
		assert(m_quackBehavior);
		SetFlyBehavior(flyBehavior);
	}
	void Quack() const
	{
		m_quackBehavior();
	}
	void Swim()
	{
		std::cout << "I'm swimming" << std::endl;
	}
	void Fly()
	{
		m_flyBehavior();
	}
	void Dance()
	{
		m_danceBehavior();
	}
	void SetFlyBehavior(FlyStrategy const& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = flyBehavior;
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;
private:
	FlyStrategy m_flyBehavior;
	QuackStrategy m_quackBehavior;
	DanceStrategy m_danceBehavior;
};
