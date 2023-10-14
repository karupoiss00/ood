#pragma once
#include <vector>
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

	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text, std::optional<size_t> position = std::nullopt) override;
	std::shared_ptr<IImage> InsertImage(const std::string& path, int width, int height, std::optional<size_t> position = std::nullopt) override;
	[[nodiscard]] size_t GetItemsCount() const override;
	[[nodiscard]] CConstDocumentItem GetItem(size_t index) const override;
	[[nodiscard]] CDocumentItem GetItem(size_t index) override;

	void DeleteItem(size_t index) override;

	void Save(const std::string& path) const override {};

private:
	std::string m_title;
	std::vector<CDocumentItem> m_items;
	CHistory m_history;
};