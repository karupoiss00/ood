#pragma once
#include <vector>
#include "AbstractCommand.h"
#include "IDocument.h"

class CInsertCommand : public CAbstractCommand
{
public:
	CInsertCommand(std::vector<CDocumentItem>& items, CDocumentItem& value, std::optional<size_t> position = std::nullopt);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::vector<CDocumentItem>& m_items;
	CDocumentItem& m_value;
	std::optional<size_t> m_insertPos;
};