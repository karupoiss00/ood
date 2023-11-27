#pragma once
#include <iostream>
#include "MapStateToString.h"
#include "IState.h"
#include "IGumballMachine.h"

class CNoQuarterState : public IState
{
public:
	CNoQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You inserted a quarter" << std::endl;
		m_gumballMachine.SetHasQuarterState();
	}
	void EjectQuarter() override
	{
		std::cout << "You haven't inserted a quarter" << std::endl;
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no quarter" << std::endl;
	}
	void Dispense() override
	{
		std::cout << "You need to pay first" << std::endl;
	}
	std::string ToString() const override
	{
		return STATE_STRING_MAP.at(State::NO_QUARTER);
	}

private:
	IGumballMachine& m_gumballMachine;
};
