#pragma once
#include "IDocument.h"
#include "History.h"

class CDocument: public IDocument
{
public:
	void SetTitle(const std::string & title) override;
	[[nodiscard]] std::string GetTitle() const override;

	[[nodiscard]] bool CanUndo() const override;	
	void Undo() override;
	[[nodiscard]] bool CanRedo() const override;
	void Redo() override;

	virtual std::shared_ptr<IParagraph> InsertParagraph(const std::string& text, std::optional<size_t> position = std::nullopt) { return nullptr; };
	virtual std::shared_ptr<IImage> InsertImage(const std::string& path, int width, int height, std::optional<size_t> position = std::nullopt) { return nullptr; };
	[[nodiscard]] virtual size_t GetItemsCount() const {return 1;};
	[[nodiscard]] virtual CConstDocumentItem GetItem(size_t index) const { return CConstDocumentItem(); };
	virtual CDocumentItem GetItem(size_t index) { return CDocumentItem(); };

	virtual void DeleteItem(size_t index) {};
	virtual void Save(const std::string& path) const {};

private:
	std::string m_title;
	CHistory m_history;
};