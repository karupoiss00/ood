#include <stdexcept>
#include <boost/filesystem.hpp>
#include "Core.h"
#include "Paragraph.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "InsertItemCommand.h"
#include "DeleteItemCommand.h"
#include "Image.h"

using namespace std;
namespace fs = boost::filesystem;


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
	CParagraph paragraph(text, *this);
	CDocumentItem item(make_shared<CParagraph>(paragraph));

	m_history.AddAndExecuteCommand(make_unique<CInsertItemCommand>(m_items, make_shared<CDocumentItem>(item), position));

	return item.GetParagraph();
}

std::shared_ptr<IImage> CDocument::InsertImage(const std::string& path, int width, int height, std::optional<size_t> position)
{
	Core::AssertImageSize(width, height);

	if (!fs::exists(path))
	{
		throw logic_error("The file " + path + " does not exist");
	}

	const auto filename = Core::GenerateRandomFileName(Core::TEMP_FILE_NAME_LENGTH);
	const auto extension = fs::path(path).extension().string();
	string to = m_tempFolder.string() + "\\" + filename + extension;
	fs::copy_file(path, to);

	auto image = make_shared<CImage>(to, width, height, *this);
	auto item = make_shared<CDocumentItem>(image);

	AddAndExecuteCommand(make_unique<CInsertItemCommand>(m_items, item, position));

	return image;
}

std::shared_ptr<CConstDocumentItem> CDocument::GetItem(size_t index) const
{
	if (index > m_items.size())
	{
		throw out_of_range("item index out of document range");
	}

	return m_items[index];
}

std::shared_ptr<CDocumentItem> CDocument::GetItem(size_t index)
{
	if (index > m_items.size())
	{
		throw out_of_range("item index out of document range");
	}

	return m_items[index];
}

void CDocument::DeleteItem(size_t index)
{
	m_history.AddAndExecuteCommand(make_unique<CDeleteItemCommand>(m_items, index));
}

void CDocument::AddAndExecuteCommand(ICommandPtr&& command)
{
	m_history.AddAndExecuteCommand(std::move(command));
}