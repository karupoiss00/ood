#pragma once
#include "ICommand.h"
	
class ICommandExecutor
{
public:
	virtual ~ICommandExecutor() = default;

	virtual void AddAndExecuteCommand(ICommandPtr&& command) = 0;
};