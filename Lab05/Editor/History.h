#pragma once
#include <deque>
#include "ICommand_fwd.h"
#include "ICommonExecutor.h"

class CHistory : public ICommonExecutor
{
public:
	CHistory();
	~CHistory();

	bool CanUndo()const;	
	void Undo();
	bool CanRedo()const;
	void Redo();
	void AddAndExecuteCommand(ICommandPtr && command) override;
private:
	std::deque<ICommandPtr> m_commands;
	size_t m_nextCommandIndex = 0;
};

// ограничить историю команд для проверки очистки ресурсов