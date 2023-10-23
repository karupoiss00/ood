#include <catch2/catch.hpp>
#include "DocumentItem.h"
#include "IImage.h"
#include "IParagraph.h"
#include "Image.h"
#include "MockHistoryController.h"
#include "Paragraph.h"

using namespace std;

struct DocumentItemFixture
{
	DocumentItemFixture()
		: f_paragraph(make_shared<CParagraph>("text", historyController))
		, f_image(make_shared<CImage>("C:/image/image.jpg", 800, 600, historyController))
	{
	}

	CMockHistoryController historyController;

	shared_ptr<IParagraph> f_paragraph;
	shared_ptr<IImage> f_image;
};

TEST_CASE_METHOD(DocumentItemFixture, "paragraph available")
{
	CDocumentItem item(move(f_paragraph));
	REQUIRE(item.GetParagraph() != nullptr);
	REQUIRE(item.GetImage() == nullptr);
}

TEST_CASE_METHOD(DocumentItemFixture, "image available")
{
	CDocumentItem item(move(f_image));
	REQUIRE(item.GetParagraph() == nullptr);
	REQUIRE(item.GetImage() != nullptr);
}

TEST_CASE_METHOD(DocumentItemFixture, "item is paragraph")
{
	SECTION("must return pointer to paragraph")
	{
		CDocumentItem item(move(f_paragraph));
		auto paragraph = item.GetParagraph();

		REQUIRE(paragraph == f_paragraph);
	}
}

TEST_CASE_METHOD(DocumentItemFixture, "item is image")
{
	SECTION("must return pointer to paragraph")
	{
		CDocumentItem item(move(f_image));
		auto image = item.GetImage();

		REQUIRE(image == f_image);
	}
}