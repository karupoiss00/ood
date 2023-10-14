#include <stdexcept>
#include "Paragraph.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "InsertCommand.h"

using namespace std;

void CDocument::SetTitle(const std::string & title)
{
	m_history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(m_title, title));
}

std::string CDocument::GetTitle() const
{
	return m_title;
}

bool CDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void CDocument::Undo()
{
	m_history.Undo();
}

bool CDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void CDocument::Redo()
{
	m_history.Redo();
}

size_t CDocument::GetItemsCount() const
{
	return m_items.size();
}

std::shared_ptr<IParagraph> CDocument::InsertParagraph(const std::string& text, std::optional<size_t> position)
{
	CParagraph paragraph(text);
	CDocumentItem item(make_shared<CParagraph>(paragraph));

	m_history.AddAndExecuteCommand(make_unique<CInsertCommand>(m_items, item, position));

	return item.GetParagraph();
}

std::shared_ptr<IImage> CDocument::InsertImage(const std::string& path, int width, int height, std::optional<size_t> position)
{
	return nullptr;
}

CConstDocumentItem CDocument::GetItem(size_t index) const
{
	if (index > m_items.size())
	{
		throw out_of_range("item index out of document range");
	}

	return m_items[index];
}

CDocumentItem CDocument::GetItem(size_t index)
{
	if (index > m_items.size())
	{
		throw out_of_range("item index out of document range");
	}

	return m_items[index];
}

void CDocument::DeleteItem(size_t index)
{
	
}