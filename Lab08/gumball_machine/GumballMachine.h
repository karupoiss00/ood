#pragma once
#include <iostream>
#include <format>
#include "IState.h"
#include "HasQuarterState.h"
#include "NoQuarterState.h"
#include "SoldOutState.h"
#include "SoldState.h"
#include "IGumballMachine.h"

class CGumballMachine : private IGumballMachine
{
public:
	CGumballMachine(unsigned numBalls, std::ostream& out)
		: m_soldState(*this)
		, m_soldOutState(*this)
		, m_noQuarterState(*this)
		, m_hasQuarterState(*this)
		, m_state(&m_soldOutState)
		, m_gumballsCount(numBalls)
		, m_out(out)
	{
		if (m_gumballsCount > 0)
		{
			m_state = &m_noQuarterState;
		}
	}

	void EjectQuarter()
	{
		m_state->EjectQuarter();
	}

	void InsertQuarter()
	{
		m_state->InsertQuarter();
	}

	void TurnCrank()
	{
		m_state->TurnCrank();
	}

	std::string ToString() const
	{
		return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2023
Inventory: {} gumball{}
Machine is {}
)",
			m_gumballsCount, m_gumballsCount != 1 ? "s" : "", m_state->ToString());
	}

	std::string GetStateString() 
	{
		return m_state->ToString();
	}

private:
	unsigned GetBallCount() const override
	{
		return m_gumballsCount;
	}

	void Dispense() override 
	{
		m_state->Dispense();
	}

	virtual void ReleaseBall() override
	{
		if (m_gumballsCount != 0)
		{
			std::cout << "A gumball comes rolling out the slot..." << std::endl;
			--m_gumballsCount;
		}
	}

	void SetSoldOutState() override
	{
		m_state = &m_soldOutState;
	}

	void SetNoQuarterState() override
	{
		m_state = &m_noQuarterState;
	}

	void SetSoldState() override
	{
		m_state = &m_soldState;
	}

	void SetHasQuarterState() override
	{
		m_state = &m_hasQuarterState;
	}

private:
	unsigned m_gumballsCount = 0;
	CSoldState m_soldState;
	CSoldOutState m_soldOutState;
	CNoQuarterState m_noQuarterState;
	CHasQuarterState m_hasQuarterState;
	IState* m_state;

	std::ostream& m_out;
};