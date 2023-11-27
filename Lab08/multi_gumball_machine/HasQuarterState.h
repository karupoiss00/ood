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
		m_gumballMachine.AddQuarter();
	}
	void EjectQuarter() override
	{
		m_gumballMachine.ReleaseAllQuarters();
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
	const unsigned MAX_QUARTERS_COUNT = 5;

	IGumballMachine& m_gumballMachine;
};
