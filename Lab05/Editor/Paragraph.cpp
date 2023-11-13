#include "Paragraph.h"
#include "FunctionalCommand.h"

CParagraph::CParagraph(std::string text, ICommandExecutor& historyController)
	: m_content(std::move(text))
	, m_historyController(historyController)
{}

std::string CParagraph::GetText() const
{
	return m_content;
}

void CParagraph::SetText(const std::string& text)
{
	auto oldContent = m_content;

	m_historyController.AddAndExecuteCommand(std::make_unique<FunctionalCommand>(
		[this, text]() {
			this->m_content = text;
		},
		[this, oldContent]() {
			this->m_content = oldContent;
		}
	));
}
