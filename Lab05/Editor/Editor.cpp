#include <fstream>
#include "Editor.h"

#include "Core.h"

using namespace std;
using namespace std::placeholders;

namespace fs = boost::filesystem;

CEditor::CEditor()
{
	auto help = [this](istream&) { m_menu.ShowInstructions(); };
	auto exit = [this](istream&) { m_menu.Exit(); };
	auto undo = [this](istream& in) { this->Undo(in); };
	auto redo = [this](istream& in) { this->Redo(in); };
	auto list = [this](istream& in) { this->List(in); };
	auto setTitle = [this](istream& in) { this->SetTitle(in); };
	auto insertParagraph = [this](istream& in) { this->InsertParagraph(in); };
	auto insertImage = [this](istream& in) { this->InsertImage(in); };
	auto replaceText = [this](istream& in) { this->ReplaceText(in); };
	auto resizeImage = [this](istream& in) { this->ResizeImage(in); };
	auto deleteItem = [this](istream& in) { this->DeleteItem(in); };

	AddMenuItem("undo", "Undo command", undo);
	AddMenuItem("redo", "Redo undone command", redo);
	AddMenuItem("help", "Help", help);
	AddMenuItem("exit", "Exit", exit);
	AddMenuItem("list", "Show document", list);
	AddMenuItem("settitle", "Changes title. Args: <new title>", setTitle);
	AddMenuItem("insertparagraph", "Inserts paragraph. Args: <pos>|end <text>", insertParagraph);
	AddMenuItem("insertimage", "Inserts image", insertImage);
	AddMenuItem("replacetext", "Replacing text in paragraph", replaceText);
	AddMenuItem("resizeimage", "Resizing image", resizeImage);
	AddMenuItem("deleteitem", "Delete item. Args: <pos>", deleteItem);

	CreateTempFolder();

	m_document = make_unique<CDocument>(m_tempFolder);
}

CEditor::~CEditor()
{
	DeleteTempFolder();
}

void CEditor::Start()
{
	m_menu.Run();
}

void CEditor::AddMenuItem(const string& shortcut, const string& description, MenuHandlerFn handler)
{
	m_menu.AddItem(shortcut, description, handler);
}

void CEditor::SetTitle(istream& in) const
{
	string head;
	string tail;

	if (in >> head)
	{
		getline(in, tail);
	}
	const string title = head + tail;

	m_document->SetTitle(title);
}

void CEditor::List(istream&) const
{
	cout << "-------------" << endl;
	cout << m_document->GetTitle() << endl;
	cout << "-------------" << endl;

	for (size_t i = 0; i < m_document->GetItemsCount(); i++)
	{
		auto item = m_document->GetItem(i);

		cout << i + 1 << ". ";

		auto paragraph = item->GetParagraph();
		if (paragraph)
		{
			cout << "Paragraph:" << paragraph->GetText() << endl;
		}
	}
}

void CEditor::Undo(istream&) const
{
	if (m_document->CanUndo())
	{
		m_document->Undo();
	}
	else
	{
		throw logic_error("Can't undo");
	}
}

void CEditor::Redo(istream&) const
{
	if (m_document->CanRedo())
	{
		m_document->Redo();
	}
	else
	{
		throw logic_error("Can't redo");
	}
}

void CEditor::InsertParagraph(istream& in) const
{
	string positionArgument;
	string valueArgument;

	in >> positionArgument;

	if (positionArgument.empty())
	{
		throw invalid_argument("Invalid InsertParagraph syntax. Check help.");
	}

	getline(in, valueArgument);

	size_t pos;
	if (Core::ParseNumber(positionArgument, pos))
	{
		m_document->InsertParagraph(valueArgument, pos);
	}
	else
	{
		m_document->InsertParagraph(valueArgument);
	}
}

void CEditor::ReplaceText(istream& in) const
{
	string positionArgument;
	string valueArgument;

	in >> positionArgument;

	size_t pos;
	if (!Core::ParseNumber(positionArgument, pos))
	{
		throw invalid_argument("Invalid ReplaceText syntax. Check help.");
	}

	auto paragraph = m_document->GetItem(pos)->GetParagraph();
	if (paragraph == nullptr)
	{
		throw logic_error("This item is not a paragraph");
	}

	getline(in, valueArgument);
	paragraph->SetText(valueArgument);
}

void CEditor::DeleteItem(istream& in) const
{
	string positionArgument;
	in >> positionArgument;

	size_t pos;

	if (Core::ParseNumber(positionArgument, pos))
	{
		m_document->DeleteItem(pos);
	}
	else
	{
		throw invalid_argument("Invalid DeleteItem syntax. Check help.");
	}
}

void CEditor::InsertImage(istream& in) const
{
	string posStr, widthStr, heightStr, filePath;
	
	in >> posStr >> widthStr >> heightStr >> filePath;

	size_t pos, width, height;
	const bool posParsed = Core::ParseNumber(posStr, pos);
	if (posParsed 
		|| posStr == "end"
		|| !Core::ParseNumber(widthStr, width)
		|| !Core::ParseNumber(heightStr, height))
	{
		throw invalid_argument("Invalid InsertImage syntax. Check help.");
	}

	if (posParsed)
	{
		m_document->InsertImage(filePath, width, height, pos);
	}
	else
	{
		m_document->InsertImage(filePath, width, height);
	}
}

void CEditor::ResizeImage(istream& in) const
{
	string posStr, widthStr, heightStr;

	in >> posStr >> widthStr >> heightStr;

	size_t pos, width, height;

	if (!Core::ParseNumber(posStr, pos)
		|| !Core::ParseNumber(widthStr, width)
		|| !Core::ParseNumber(heightStr, height))
	{
		throw invalid_argument("Invalid ResizeImage syntax. Check help.");
	}


	Core::AssertImageSize(width, height);
	const auto image = m_document->GetItem(pos)->GetImage();

	if (image == nullptr)
	{
		throw logic_error("This item is not a image");
	}

	image->Resize(width, height);

}

void CEditor::Save(istream& in) const
{
	string fileName;

	in >> fileName;

	const fs::path outputFilePath(fileName);

	if (fs::exists(fileName))
	{
		throw logic_error("File already exists");
	}

	if (outputFilePath.extension() != ".html")
	{
		throw logic_error("Invalid filename");
	}

	const string parentPath = outputFilePath.parent_path().string();
	string imageFolderName = parentPath + "\\" + outputFilePath.stem().string() + "_images";

	if (!fs::exists(parentPath))
	{
		fs::create_directory(parentPath);
	}

	ofstream outputFile(outputFilePath.string());

	if (outputFile.is_open())
	{
		Core::SaveDocumentToHtml(m_document, outputFile, imageFolderName);
	}
	else
	{
		throw logic_error("An error occurred when writing file");
	}
}

void CEditor::CreateTempFolder()
{
	m_tempFolder = fs::current_path().string() + "\\" + Core::GenerateRandomFileName(Core::TEMP_FOLDER_NAME_LENGTH);

	if (fs::exists(m_tempFolder))
	{
		DeleteTempFolder();
	}

	fs::create_directory(m_tempFolder);
}

void CEditor::DeleteTempFolder()
{
	fs::remove_all(m_tempFolder);
}
