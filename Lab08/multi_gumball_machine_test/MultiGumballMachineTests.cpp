#include "GumballMachine.h"
#include "IGumballMachine.h"
#include "MapStateToString.h"
#include <catch2/catch.hpp>

const unsigned NUM_BALLS = 5;

std::string GetStateString(State state)
{
	return STATE_STRING_MAP.at(state);
}

struct GumballMachineFixtureBase
{
	GumballMachineFixtureBase(unsigned numBalls)
		: machine(CGumballMachine(numBalls, strm))
	{
	}

	std::stringstream strm;
	CGumballMachine machine;

	IGumballMachine* operator--(int)
	{
		return reinterpret_cast<IGumballMachine*>(&machine);
	}
};

struct FilledGumballMachineFixture : public GumballMachineFixtureBase
{
	FilledGumballMachineFixture()
		: GumballMachineFixtureBase(NUM_BALLS)
	{
	}
};

TEST_CASE_METHOD(FilledGumballMachineFixture, "GumballMachine")
{
	SECTION("InNoQuarterState")
	{
		auto& fixture = *this;
		REQUIRE(machine.GetStateString() == GetStateString(State::NO_QUARTER));

		SECTION("AllowsInsertAQuarter")
		{
			machine.InsertQuarter();
			REQUIRE(machine.GetStateString() == GetStateString(State::HAS_QUARTER));
		}

		SECTION("IgnoresAllOtherActions")
		{
			machine.EjectQuarter();
			REQUIRE(machine.GetStateString() == GetStateString(State::NO_QUARTER));

			machine.TurnCrank();
			REQUIRE(machine.GetStateString() == GetStateString(State::NO_QUARTER));
		
			fixture--->Dispense();
			REQUIRE(machine.GetStateString() == GetStateString(State::NO_QUARTER));
		}
	}

	SECTION("InHasQuarterState")
	{
		auto& fixture = *this;
		fixture--->SetHasQuarterState();

		REQUIRE(machine.GetStateString() == GetStateString(State::HAS_QUARTER));

		SECTION("AllowsEjectQuarter")
		{
			machine.EjectQuarter();
			REQUIRE(machine.GetStateString() == GetStateString(State::NO_QUARTER));
		}

		SECTION("AfterTurnOfCrank")
		{
			auto ballCountBeforeTurnCrank = fixture--->GetBallCount();

			machine.TurnCrank();
			REQUIRE(fixture--->GetBallCount() == --ballCountBeforeTurnCrank);
		}

		SECTION("NotAllowsInsertAQuarter")
		{
			machine.InsertQuarter();
			REQUIRE(machine.GetStateString() == GetStateString(State::HAS_QUARTER));
		}

		SECTION("MaxQuartersCount")
		{
			machine.InsertQuarter();
			machine.InsertQuarter();
			machine.InsertQuarter();
			machine.InsertQuarter();
			machine.InsertQuarter();
			machine.InsertQuarter();

			REQUIRE(fixture--->GetQuarterCount() == 5);
		}

		SECTION("KeepHasQuarterStateIfQuartersLeft")
		{
			machine.InsertQuarter();
			machine.InsertQuarter();

			auto prevBallsCount = fixture--->GetBallCount();
			machine.TurnCrank();

			REQUIRE(machine.GetStateString() == GetStateString(State::HAS_QUARTER));
			REQUIRE(prevBallsCount == fixture--->GetBallCount() + 1);
		}

		SECTION("Ignore dispense")
		{
			fixture--->Dispense();
			REQUIRE(machine.GetStateString() == GetStateString(State::HAS_QUARTER));	
		}
	}

	SECTION("InSoldState")
	{
		auto& fixture = *this;
		fixture--->SetSoldState();

		REQUIRE(machine.GetStateString() == GetStateString(State::SOLD));

		SECTION("DispenseOneBallAndChangesTheState")
		{
			SECTION("ToNoQuarterState")
			{
				CHECK(fixture--->GetBallCount() > 0);

				fixture--->Dispense();
				REQUIRE(machine.GetStateString() == GetStateString(State::NO_QUARTER));
			}

			SECTION("OrToSoldOutState")
			{
				for (unsigned i = 0; i < 4; ++i)
				{
					fixture--->ReleaseBall();
				}

				fixture--->Dispense();
				REQUIRE(machine.GetStateString() == GetStateString(State::SOLD_OUT));
			}
		}

		SECTION("IgnoresAllOtherActions")
		{
			machine.InsertQuarter();
			REQUIRE(machine.GetStateString() == GetStateString(State::SOLD));

			machine.EjectQuarter();
			REQUIRE(machine.GetStateString() == GetStateString(State::SOLD));

			machine.TurnCrank();
			REQUIRE(machine.GetStateString() == GetStateString(State::SOLD));
		}
	}
}

struct EmptyGumballMachineFixture : public GumballMachineFixtureBase
{
	EmptyGumballMachineFixture()
		: GumballMachineFixtureBase(0)
	{
	}
};

TEST_CASE_METHOD(EmptyGumballMachineFixture, "empty machine")
{
	auto& fixture = *this;
	SECTION("InSoldOutState")
	{
		REQUIRE(machine.GetStateString() == GetStateString(State::SOLD_OUT));

		SECTION("IgnoresAllActions")
		{
			machine.InsertQuarter();
			REQUIRE(machine.GetStateString() == GetStateString(State::SOLD_OUT));

			machine.EjectQuarter();
			REQUIRE(machine.GetStateString() == GetStateString(State::SOLD_OUT));

			machine.TurnCrank();
			REQUIRE(machine.GetStateString() == GetStateString(State::SOLD_OUT));
		
			fixture--->Dispense();
			REQUIRE(machine.GetStateString() == GetStateString(State::SOLD_OUT));
		}
	}
}