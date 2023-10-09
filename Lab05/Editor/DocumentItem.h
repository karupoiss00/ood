#pragma once
#include "ConstDocumentItem.h"

class CDocumentItem final : public CConstDocumentItem
{
public:
	std::shared_ptr<IImage> GetImage();
	std::shared_ptr<IParagraph> GetParagraph();
};
