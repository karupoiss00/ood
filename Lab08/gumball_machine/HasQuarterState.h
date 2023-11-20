#pragma once
#include <iostream>
#include "MapStateToString.h"
#include "IState.h"
#include "IGumballMachine.h"

class CHasQuarterState : public IState
{
public:
	CHasQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You can't insert another quarter" << std::endl;
	}
	void EjectQuarter() override
	{
		std::cout << "Quarter returned" << std::endl;
		m_gumballMachine.SetNoQuarterState();
	}
	void TurnCrank() override
	{
		std::cout << "You turned..." << std::endl;
		m_gumballMachine.SetSoldState();
		m_gumballMachine.Dispense();
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed" << std::endl;
	}
	std::string ToString() const override
	{
		return STATE_STRING_MAP.at(State::HAS_QUARTER);
	}

private:
	IGumballMachine& m_gumballMachine;
};