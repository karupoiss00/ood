#pragma once

#include "ICommand.h"

class IHistoryController
{
public:
	virtual ~IHistoryController() = default;

	virtual void AddAndExecuteCommand(ICommandPtr&& command) = 0;
};