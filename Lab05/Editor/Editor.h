#pragma once
#include "Menu.h"
#include "Document.h"


class CEditor
{
public:
	CEditor();

	void Start();

	~CEditor();
private:
	using MenuHandlerFn = std::function<void(std::istream& in)>;

	void AddMenuItem(const std::string& shortcut, const std::string& description, MenuHandlerFn handler);
	void SetTitle(std::istream& in) const;
	void List(std::istream&) const;
	void Undo(std::istream&) const;
	void Redo(std::istream&) const;
	void InsertParagraph(std::istream&) const;
	void DeleteItem(std::istream& in) const;
	void ReplaceText(std::istream&) const;
	void ResizeImage(std::istream&) const;
	void InsertImage(std::istream&) const;
	void Save(std::istream& in) const;

	void CreateTempFolder();
	void DeleteTempFolder();

	CMenu m_menu;
	std::unique_ptr<IDocument> m_document;
	std::string m_tempFolder;

};