#include <boost/filesystem.hpp>
#include "InsertItemCommand.h"

namespace fs = boost::filesystem;
using namespace std;

CInsertItemCommand::CInsertItemCommand(vector<shared_ptr<CDocumentItem>>& items, shared_ptr<CDocumentItem> const& value, std::optional<size_t> position)
	: m_items(items), m_value(value), m_insertPos(position)
{
}

void CInsertItemCommand::DoExecute()
{
	const auto pos = m_insertPos.has_value()
		? m_items.begin() + static_cast<int>(m_insertPos.value())
		: m_items.end();

	m_items.insert(pos, m_value);
}

void CInsertItemCommand::DoUnexecute()
{
	const auto it = find(m_items.begin(), m_items.end(), m_value);
	m_items.erase(it);
}


CInsertItemCommand::~CInsertItemCommand()
{
	if (m_value->GetImage() != nullptr && !IsExecuted())
	{
		fs::remove(m_value->GetImage()->GetPath());
	}
}