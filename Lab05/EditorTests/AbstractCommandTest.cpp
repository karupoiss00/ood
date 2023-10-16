#include <catch2/catch.hpp>
#include "AbstractCommand.h"

using namespace std;

constexpr int VALUE_BEFORE_EXECUTE = 1;
constexpr int VALUE_AFTER_EXECUTE = 2;

class CMockAbstractCommand : public CAbstractCommand
{
public:
	CMockAbstractCommand(int& value)
		: m_value(value)
	{
	}

	bool isCommandExecute() const
	{
		return IsExecuted();
	}

protected:
	void DoExecute() override
	{
		m_value += 1;
	}

	void DoUnexecute() override
	{
		m_value -= 1;
	}

private:
	int& m_value;
};


struct AbstractCommandFixture
{
	AbstractCommandFixture()
		: value(VALUE_BEFORE_EXECUTE)
		, command(value)
	{
	}

	int value;
	CMockAbstractCommand command;
};

struct AbstractCommandExecutedFixture : AbstractCommandFixture
{
	AbstractCommandExecutedFixture()
	{
		command.Execute();
	}	
};

TEST_CASE_METHOD(AbstractCommandFixture, "constructor test")
{
	SECTION("not executed")
	{
		REQUIRE(!command.isCommandExecute());
	}
}

TEST_CASE_METHOD(AbstractCommandFixture, "not executed state")
{
	SECTION("can execute")
	{
		REQUIRE(!command.isCommandExecute());
		REQUIRE(value == VALUE_BEFORE_EXECUTE);

		command.Execute();

		REQUIRE(value == VALUE_AFTER_EXECUTE);
		REQUIRE(command.isCommandExecute());
	}

	SECTION("can not undo")
	{
		REQUIRE(value == VALUE_BEFORE_EXECUTE);

		command.Unexecute();

		REQUIRE(value == VALUE_BEFORE_EXECUTE);
	}
}

TEST_CASE_METHOD(AbstractCommandExecutedFixture, "executed state")
{
	SECTION("can undo")
	{
		REQUIRE(command.isCommandExecute());
		REQUIRE(value == VALUE_AFTER_EXECUTE);

		command.Unexecute();

		REQUIRE(value == VALUE_BEFORE_EXECUTE);
		REQUIRE(!command.isCommandExecute());
	}

	SECTION("can\'t execute")
	{
		REQUIRE(value == VALUE_AFTER_EXECUTE);

		command.Execute();

		REQUIRE(value == VALUE_AFTER_EXECUTE);
	}
}