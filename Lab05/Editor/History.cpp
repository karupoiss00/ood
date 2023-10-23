#include <cassert>
#include "History.h"
#include "ICommand.h"

using namespace std;

constexpr int MAX_HISTORY_SIZE = 2;

CHistory::CHistory()
{
}


CHistory::~CHistory()
{
}

bool CHistory::CanUndo() const
{
	return m_nextCommandIndex != 0;
}

bool CHistory::CanRedo() const
{
	return m_nextCommandIndex != m_commands.size();
}

void CHistory::Undo()
{
	if (CanUndo())
	{
		m_commands[m_nextCommandIndex - 1]->Unexecute();
		--m_nextCommandIndex;
	}
}

void CHistory::Redo()
{
	if (CanRedo())
	{
		m_commands[m_nextCommandIndex]->Execute();
		++m_nextCommandIndex;
	}
}

void CHistory::AddAndExecuteCommand(ICommandPtr && command)
{
	if (m_nextCommandIndex < m_commands.size())
	{
		command->Execute();
		++m_nextCommandIndex;

		m_commands.resize(m_nextCommandIndex);
		m_commands.back() = move(command);
	}
	else
	{
		assert(m_nextCommandIndex == m_commands.size());
		m_commands.emplace_back(nullptr);

		try
		{
			command->Execute();

			m_commands.back() = move(command);
			++m_nextCommandIndex;
			if (m_nextCommandIndex > MAX_HISTORY_SIZE)
			{
				m_commands.erase(m_commands.begin());
				--m_nextCommandIndex;
			}
		}
		catch (...)
		{
			m_commands.pop_back();
			throw;
		}
	}
}
