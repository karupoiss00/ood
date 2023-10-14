#include "DocumentItem.h"

using namespace std;

CDocumentItem::CDocumentItem(shared_ptr<IParagraph>&& paragraph)
	: m_paragraph(paragraph)
{}

CDocumentItem::CDocumentItem(shared_ptr<IImage>&& image)
	: m_image(image)
{
	
}

shared_ptr<IImage> CDocumentItem::GetImage()
{
	return m_image;
}

shared_ptr<IParagraph> CDocumentItem::GetParagraph()
{
	return m_paragraph;
}
