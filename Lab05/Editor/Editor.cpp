#include <sstream>
#include "Editor.h"

using namespace std;
using namespace std::placeholders;

CEditor::CEditor()
	: m_document(make_unique<CDocument>())
{
	AddMenuItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
	AddMenuItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
	AddMenuItem("list", "Show document", [this](istream& in) { this->List(in); });
	AddMenuItem("setTitle", "Changes title. Args: <new title>", [this](istream& in) { this->SetTitle(in); });
	AddMenuItem("insertParagraph", "Inserts paragraph. Args: <pos>|end <text>", [this](istream& in) { this->InsertParagraph(in); });
	AddMenuItem("undo", "Undo command", [this](istream& in) { this->Undo(in); });
	AddMenuItem("redo", "Redo undone command", [this](istream& in) { this->Redo(in); });
}

void CEditor::Start()
{
	m_menu.Run();
}

void CEditor::AddMenuItem(const string& shortcut, const string& description, MenuHandlerFn handler)
{
	m_menu.AddItem(shortcut, description, handler);
}

// TODO: скипнуть первый пробел элегантнее
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

		auto paragraph = item.GetParagraph();
		if (paragraph)
		{
			cout << paragraph->GetText() << endl;
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
		cout << "Can't undo" << endl;
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
		cout << "Can't redo" << endl;
	}
}

void CEditor::InsertParagraph(istream& in) const
{
	string positionArgument;
	string valueArgument;

	in >> positionArgument;

	getline(in, valueArgument);

	size_t pos;

	std::stringstream iss(positionArgument);
	iss >> pos;

	if (iss.fail())
	{
		m_document->InsertParagraph(valueArgument);
	}
	else
	{
		m_document->InsertParagraph(valueArgument, pos);
	}
}
