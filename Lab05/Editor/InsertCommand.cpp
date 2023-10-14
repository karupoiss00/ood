#include "InsertCommand.h"

using namespace std;

CInsertCommand::CInsertCommand(vector<CDocumentItem>& items, CDocumentItem& value, std::optional<size_t> position)
	: m_items(items), m_value(value), m_insertPos(position)
{
}

void CInsertCommand::DoExecute()
{
	if (m_insertPos.has_value())
	{
		m_items.insert(m_items.begin() + static_cast<int>(m_insertPos.value()), m_value);
	}
	else
	{
		m_items.emplace_back(m_value);
	}
}

void CInsertCommand::DoUnexecute()
{
	if (m_insertPos.has_value())
	{
		m_items.erase(m_items.begin() + static_cast<int>(m_insertPos.value()));
	}
	else
	{
		m_items.pop_back();
	}
}