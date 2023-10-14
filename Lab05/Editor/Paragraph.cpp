#include "Paragraph.h"

CParagraph::CParagraph(const std::string& text)
	: m_content(text) {}

std::string CParagraph::GetText() const
{
	return m_content;
}

void CParagraph::SetText(const std::string& text)
{
	m_content = text;
}
