#pragma once
#include <vector>
#include <boost/filesystem.hpp>
#include "IDocument.h"
#include "History.h"
#include "IHistoryController.h"

class CDocument: public IDocument, public IHistoryController
{
public:
	CDocument(std::string const& tempFolder);

	void SetTitle(const std::string & title) override;
	[[nodiscard]] std::string GetTitle() const override;

	[[nodiscard]] bool CanUndo() const override;	
	void Undo() override;
	[[nodiscard]] bool CanRedo() const override;
	void Redo() override;

	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text, std::optional<size_t> position = std::nullopt) override;
	std::shared_ptr<IImage> InsertImage(const std::string& path, int width, int height, std::optional<size_t> position = std::nullopt) override;
	[[nodiscard]] size_t GetItemsCount() const override;
	[[nodiscard]] std::shared_ptr<CConstDocumentItem> GetItem(size_t index) const override;
	[[nodiscard]] std::shared_ptr<CDocumentItem> GetItem(size_t index) override;

	void DeleteItem(size_t index) override;

	void Save(const std::string& path) const override {};

	void AddAndExecuteCommand(ICommandPtr&& command) override;

private:
	void AssertDocumentPosition(std::optional<size_t> position) const;

	std::string m_title;
	std::vector<std::shared_ptr<CDocumentItem>> m_items;
	CHistory m_history;
	const boost::filesystem::path m_tempFolder;
};