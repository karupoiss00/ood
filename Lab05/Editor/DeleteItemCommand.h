#pragma once
#include <vector>
#include "AbstractCommand.h"
#include "IDocument.h"

class CDeleteItemCommand : public CAbstractCommand
{
public:
	CDeleteItemCommand(std::vector<std::shared_ptr<CDocumentItem>>& items, size_t position);
	~CDeleteItemCommand();

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::vector<std::shared_ptr<CDocumentItem>>& m_items;
	std::shared_ptr<CDocumentItem> m_itemToRemove;
	size_t m_deletePos;
};