#pragma once
#include "Menu.h"
#include "Document.h"


class CEditor
{
public:
	CEditor();

	void Start();
private:
	using MenuHandlerFn = std::function<void(std::istream& in)>;

	void AddMenuItem(const std::string& shortcut, const std::string& description, MenuHandlerFn handler);
	void SetTitle(std::istream& in) const;
	void List(std::istream&) const;
	void Undo(std::istream&) const;
	void Redo(std::istream&) const;
	void InsertParagraph(std::istream&) const;

	CMenu m_menu;
	std::unique_ptr<IDocument> m_document;
};