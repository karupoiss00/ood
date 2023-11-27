#pragma once
#include <iostream>
#include "MapStateToString.h"
#include "IState.h"
#include "IGumballMachine.h"
#include "MapStateToString.h"

class CSoldOutState : public IState
{
public:
	CSoldOutState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You can't insert a quarter, the machine is sold out" << std::endl;
	}

	void EjectQuarter() override
	{
		std::cout << "You can't eject, you haven't inserted a quarter yet" << std::endl;
	}

	void TurnCrank() override
	{
		std::cout << "You turned but there's no gumballs" << std::endl;
	}

	void Dispense() override
	{
		std::cout << "No gumball dispensed" << std::endl;
	}

	std::string ToString() const override
	{
		return STATE_STRING_MAP.at(State::SOLD_OUT);
	}
private:
	IGumballMachine& m_gumballMachine;
};