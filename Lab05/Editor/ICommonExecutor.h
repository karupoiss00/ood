#pragma once
#include "ICommand.h"

// это не HistoryController, CommonExecutor, upd CommandExecutor
class ICommonExecutor
{
public:
	virtual ~ICommonExecutor() = default;

	virtual void AddAndExecuteCommand(ICommandPtr&& command) = 0;
};