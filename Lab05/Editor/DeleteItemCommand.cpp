#include <boost/filesystem.hpp>
#include "DeleteItemCommand.h"

namespace fs = boost::filesystem;
using namespace std;

CDeleteItemCommand::CDeleteItemCommand(std::vector<std::shared_ptr<CDocumentItem>>& items, size_t position)
	: m_items(items), m_itemToRemove(m_items.at(position)), m_deletePos(position)
{
}

void CDeleteItemCommand::DoExecute()
{
	const auto it = find(m_items.begin(), m_items.end(), m_itemToRemove);
	m_items.erase(it);
}

void CDeleteItemCommand::DoUnexecute()
{
	m_items.insert(m_items.begin() + static_cast<int>(m_deletePos), m_itemToRemove);
}

CDeleteItemCommand::~CDeleteItemCommand()
{
	auto image = m_itemToRemove->GetImage();
	if (image != nullptr && IsExecuted())
	{
		fs::remove(image->GetPath());
	}
}