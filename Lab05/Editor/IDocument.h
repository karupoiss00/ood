#pragma once
#include <memory>
#include <string>
#include <optional>
#include "IParagraph.h"
#include "IImage.h"
#include "ConstDocumentItem.h"
#include "DocumentItem.h"

class IDocument
{
public:
	virtual std::shared_ptr<IParagraph> InsertParagraph(const std::string& text, std::optional<size_t> position = std::nullopt) = 0;
	virtual std::shared_ptr<IImage> InsertImage(const std::string& path, int width, int height,std::optional<size_t> position = std::nullopt) = 0;
	[[nodiscard]] virtual size_t GetItemsCount() const = 0;
	[[nodiscard]] virtual CConstDocumentItem GetItem(size_t index) const = 0;
	virtual CDocumentItem GetItem(size_t index) = 0;
	virtual void DeleteItem(size_t index) = 0;
	[[nodiscard]] virtual std::string GetTitle() const = 0;
	virtual void SetTitle(const std::string& title) = 0;
	[[nodiscard]] virtual bool CanUndo() const = 0;
	virtual void Undo() = 0;
	[[nodiscard]] virtual bool CanRedo() const = 0;
	virtual void Redo() = 0;
	virtual void Save(const std::string& path) const = 0;

	virtual ~IDocument() = default;
};