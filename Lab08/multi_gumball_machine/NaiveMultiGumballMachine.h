#pragma once

#include <format>
#include <iostream>
#include "IGumballMachine.h"
#include "MapStateToString.h"

class CNaiveMultipleGumballMachine : public IGumballMachine
{
public:
	CNaiveMultipleGumballMachine(unsigned count)
		: m_gumballsCount(count)
		, m_quartersCount(0)
		, m_state(count > 0 ? State::NO_QUARTER : State::SOLD_OUT)
	{
	}

	void InsertQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SOLD_OUT:
			cout << "You can't insert a quarter, the machine is SOLD out\n";
			break;
		case State::NO_QUARTER:
			cout << "You inserted a quarter\n";
			AddQuarter();
			m_state = State::HAS_QUARTER;
			break;
		case State::HAS_QUARTER:
			AddQuarter();
			break;
		case State::SOLD:
			cout << "Please wait, we're already giving you a gumball\n";
			break;
		}
	}

	void EjectQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::HAS_QUARTER:
			cout << "Quarter returned\n";
			ReleaseAllQuarters();
			break;
		case State::NO_QUARTER:
			cout << "You haven't inserted a quarter\n";
			break;
		case State::SOLD:
			cout << "Sorry you already turned the crank\n";
			break;
		case State::SOLD_OUT:
			cout << "You can't eject, you haven't inserted a quarter yet\n";
			break;
		}
	}

	void TurnCrank()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SOLD_OUT:
			cout << "You turned but there's no gumballs\n";
			break;
		case State::NO_QUARTER:
			cout << "You turned but there's no quarter\n";
			break;
		case State::HAS_QUARTER:
			cout << "You turned...\n";
			m_state = State::SOLD;
			Dispense();
			break;
		case State::SOLD:
			cout << "Turning twice doesn't get you another gumball\n";
			break;
		}
	}

	void Refill(unsigned numBalls)
	{
		m_gumballsCount = numBalls;
		m_state = numBalls > 0 ? State::NO_QUARTER : State::SOLD_OUT;
	}

	std::string ToString() const
	{
		std::string state = (m_state == State::SOLD_OUT) ? "SOLD out" : (m_state == State::NO_QUARTER) ? "waiting for quarter"
			: (m_state == State::HAS_QUARTER)														 ? "waiting for turn of crank"
																									 : "delivering a gumball";
		return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: {} gumball{}
Machine is {}
)", m_gumballsCount, (m_gumballsCount != 1 ? "s" : ""), state);
	}

	void AddQuarter()
	{
		if (m_quartersCount < 5)
		{
			m_quartersCount++;
		}
	}

	void ReleaseAllQuarters()
	{
		m_quartersCount = 0;
		SetNoQuarterState();
	}

	void TakeQuarter()
	{
		if (m_quartersCount > 0)
		{
			m_quartersCount--;
		}

		if (m_quartersCount == 0)
		{
			SetNoQuarterState();
		}
	}

	unsigned GetQuarterCount() const override
	{
		return m_quartersCount;
	}

	unsigned GetBallCount() const override
	{
		return m_gumballsCount;
	}


	virtual void ReleaseBall() 
	{
		if (m_gumballsCount > 0)
		{
			--m_gumballsCount;
		}
	}

	std::string GetStateString() const
	{
		return STATE_STRING_MAP.at(m_state);
	}

private:
	void Dispense()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SOLD:
			cout << "A gumball comes rolling out the slot\n";
			ReleaseBall();
			TakeQuarter();
			if (m_gumballsCount == 0)
			{
				cout << "Oops, out of gumballs\n";
				SetSoldOutState();
			}
			else
			{
				m_state = m_quartersCount > 0 ? State::HAS_QUARTER : State::NO_QUARTER;
			}
			break;
		case State::NO_QUARTER:
			cout << "You need to pay first\n";
			break;
		case State::SOLD_OUT:
		case State::HAS_QUARTER:
			cout << "No gumball dispensed\n";
			break;
		}
	}

	void SetSoldOutState()
	{
		m_state = State::SOLD_OUT;
	};

	void SetNoQuarterState()
	{
		m_state = State::NO_QUARTER;
	};

	void SetSoldState()
	{
		m_state = State::SOLD;
	};

	void SetHasQuarterState()
	{
		m_state = State::HAS_QUARTER;
	};

	unsigned m_gumballsCount;
	unsigned m_quartersCount;
	State m_state = State::SOLD_OUT;
};