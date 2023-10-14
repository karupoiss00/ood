#pragma once
#include <memory>
#include "IParagraph.h"
#include "IHistoryController.h"

class CParagraphImpl;

class CParagraph: public IParagraph
{
public:
	CParagraph(std::string text, IHistoryController& historyController);

	std::string GetText() const override;
	void SetText(const std::string& text) override;
private:
	std::string m_content;

	IHistoryController& m_historyController;
};

