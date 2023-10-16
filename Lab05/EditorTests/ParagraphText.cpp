#include <catch2/catch.hpp>
#include "MockHistoryController.h"
#include "Paragraph.h"

using namespace std;

struct ParagraphFixture
{
	ParagraphFixture()
		: paragraph("init", historyController)
	{
	}

	CMockHistoryController historyController;
	CParagraph paragraph;
};

TEST_CASE_METHOD(ParagraphFixture, "creating paragraph")
{
	SECTION("has text")
	{
		REQUIRE(paragraph.GetText() == "init");
	}

	SECTION("undo/redo working")
	{
		paragraph.SetText("changed");
		REQUIRE(paragraph.GetText() == "changed");

		historyController.Undo();
		REQUIRE(paragraph.GetText() == "init");

		historyController.Redo();
		REQUIRE(paragraph.GetText() == "changed");
	}
}
