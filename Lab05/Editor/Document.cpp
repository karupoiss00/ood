#include <stdexcept>
#include <filesystem>
#include "Core.h"
#include "Paragraph.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "InsertItemCommand.h"
#include "DeleteItemCommand.h"
#include "Image.h"

using namespace std;
namespace fs = std::filesystem;


CDocument::CDocument(std::string const& tempFolder)
	: m_tempFolder(tempFolder)
{}

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
	AssertDocumentPosition(position);

	CParagraph paragraph(text, m_history);
	CDocumentItem item(make_shared<CParagraph>(paragraph));

	m_history.AddAndExecuteCommand(make_unique<CInsertItemCommand>(m_items, make_shared<CDocumentItem>(item), position));

	return item.GetParagraph();
}

std::shared_ptr<IImage> CDocument::InsertImage(const std::string& path, int width, int height, std::optional<size_t> position)
{
	Core::AssertImageSize(width, height);
	AssertDocumentPosition(position);

	if (!fs::exists(path))
	{
		throw logic_error("The file " + path + " does not exist");
	}

	const auto filename = Core::GenerateRandomFileName(Core::TEMP_FILE_NAME_LENGTH);
	const auto extension = fs::path(path).extension().string();
	string to = m_tempFolder.string() + "/" + filename + extension;
	fs::copy_file(path, to);

	auto image = make_shared<CImage>(to, width, height, m_history);
	auto item = make_shared<CDocumentItem>(image);

	m_history.AddAndExecuteCommand(make_unique<CInsertItemCommand>(m_items, item, position));

	return image;
}

std::shared_ptr<CConstDocumentItem> CDocument::GetItem(size_t index) const
{
	AssertDocumentPosition(index);
	return m_items.at(index);
}

std::shared_ptr<CDocumentItem> CDocument::GetItem(size_t index)
{
	AssertDocumentPosition(index);
	return m_items.at(index);
}

void CDocument::DeleteItem(size_t index)
{
	AssertDocumentPosition(index);
	m_history.AddAndExecuteCommand(make_unique<CDeleteItemCommand>(m_items, index));
}

void CDocument::AssertDocumentPosition(optional<size_t> position) const
{
	if (position.has_value() && position.value() > m_items.size())
	{
		throw out_of_range("item position out of document range");
	}
}