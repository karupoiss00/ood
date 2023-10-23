#pragma once
#include <memory>
#include "IParagraph.h"
#include "ICommonExecutor.h"

class CParagraphImpl;

class CParagraph: public IParagraph
{
public:
	CParagraph(std::string text, ICommonExecutor& historyController);

	std::string GetText() const override;
	void SetText(const std::string& text) override;
private:
	std::string m_content;

	ICommonExecutor& m_historyController;
};

