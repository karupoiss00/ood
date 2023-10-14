#pragma once
#include <vector>
#include "AbstractCommand.h"
#include "IDocument.h"

class CInsertItemCommand : public CAbstractCommand
{
public:
	CInsertItemCommand(std::vector<std::shared_ptr<CDocumentItem>>& items, std::shared_ptr<CDocumentItem> const& value, std::optional<size_t> position = std::nullopt);
	~CInsertItemCommand() override;

protected:
	void DoExecute() override;
	void DoUnexecute() override;
private:
	std::vector<std::shared_ptr<CDocumentItem>>& m_items;
	std::shared_ptr<CDocumentItem> m_value;
	std::optional<size_t> m_insertPos;
};