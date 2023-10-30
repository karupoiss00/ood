#pragma once
#include "ICommand.h"

// ��� �� HistoryController, CommonExecutor, upd CommandExecutor
class ICommonExecutor
{
public:
	virtual ~ICommonExecutor() = default;

	virtual void AddAndExecuteCommand(ICommandPtr&& command) = 0;
};