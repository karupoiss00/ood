#pragma once


#include "History.h"
#include "IHistoryController.h"

class CMockHistoryController : public IHistoryController
{
public:
	void AddAndExecuteCommand(ICommandPtr&& command) override
	{
		m_history.AddAndExecuteCommand(move(command));
	}

	bool CanUndo() const
	{
		return m_history.CanUndo();
	}

	void Undo()
	{
		m_history.Undo();
	}

	bool CanRedo() const
	{
		return m_history.CanRedo();
	}

	void Redo()
	{
		m_history.Redo();
	}

private:
	CHistory m_history;
};