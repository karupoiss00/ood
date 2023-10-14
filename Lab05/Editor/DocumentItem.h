#pragma once
#include "ConstDocumentItem.h"

class CDocumentItem final : public CConstDocumentItem
{
public:
	CDocumentItem(std::shared_ptr<IParagraph>&& paragraph);
	CDocumentItem(std::shared_ptr<IImage>&& image);

	std::shared_ptr<IImage> GetImage();
	std::shared_ptr<IParagraph> GetParagraph();
private:
	std::shared_ptr<IParagraph> m_paragraph;
	std::shared_ptr<IImage> m_image;
};
