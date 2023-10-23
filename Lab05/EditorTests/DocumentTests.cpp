#include <optional>
#include <catch2/catch.hpp>
#include <fstream>
#include "Document.h"
#include "Core.h"

using namespace std;
namespace fs = boost::filesystem;

const string TEMP_FOLDER = fs::current_path().string() + "/tmp";
const string TEST_IMAGE = fs::current_path().string() + "/mock_data/test.bmp";

struct DocumentFixtureBase
{
	DocumentFixtureBase()
	{
		if (fs::exists(TEMP_FOLDER))
		{
			fs::remove_all(TEMP_FOLDER);
		}

		fs::create_directory(TEMP_FOLDER);
	}

	~DocumentFixtureBase()
	{
		fs::remove_all(TEMP_FOLDER);
	}
};

struct DocumentFixture : DocumentFixtureBase
{
	DocumentFixture()
		: document(TEMP_FOLDER)
	{
	}

	CDocument document;
};

void TestInsertItem(IDocument& document, optional<size_t> index, const function<void()>& insertFn, const function<void(const shared_ptr<CDocumentItem>& item)>& testFn)
{
	size_t beforeItemsCount = document.GetItemsCount();

	insertFn();

	REQUIRE(document.GetItemsCount() == beforeItemsCount + 1);

	auto insertIndex = index ? index.value() : document.GetItemsCount() - 1;
	auto item = document.GetItem(insertIndex);

	testFn(item);

	document.Undo();
	REQUIRE(document.GetItemsCount() == beforeItemsCount);

	if (insertIndex == document.GetItemsCount())
	{
		REQUIRE_THROWS_AS(document.GetItem(insertIndex), out_of_range);
	}
	else
	{
		REQUIRE(item != document.GetItem(insertIndex));
	}

	document.Redo();
	REQUIRE(document.GetItemsCount() == beforeItemsCount + 1);
	REQUIRE(item == document.GetItem(insertIndex));
}

void TestInsertParagraph(IDocument& document, const string& text, optional<size_t> index)
{
	auto insertFn = [&]() {
		document.InsertParagraph(text, index);
	};

	auto testFn = [&](const shared_ptr<CDocumentItem>& item) {
		REQUIRE(item->GetParagraph() != nullptr);
		REQUIRE(item->GetParagraph()->GetText() == text);
	};

	TestInsertItem(document, index, insertFn, testFn);
}

void TestInsertImage(IDocument& document, const string& from, int width, int height, optional<size_t> index)
{
	auto insertFn = [&]() {
		document.InsertImage(from, width, height, index);
	};

	auto testFn = [&](const shared_ptr<CDocumentItem>& item) {
		REQUIRE(item->GetImage() != nullptr);
		REQUIRE(item->GetImage()->GetWidth() == width);
		REQUIRE(item->GetImage()->GetHeight() == height);
	};

	TestInsertItem(document, index, insertFn, testFn);
}


TEST_CASE_METHOD(DocumentFixture, "Document")
{

	THEN("without title")
	{
		REQUIRE(document.GetTitle() == "");
	}

	THEN("without items")
	{
		REQUIRE(document.GetItemsCount() == 0);
	}

	THEN("undo unavailable")
	{
		REQUIRE(!document.CanUndo());
	}

	THEN("redo unavailable")
	{
		REQUIRE(!document.CanRedo());
	}

	THEN("can change title")
	{
		document.SetTitle("Title");
		REQUIRE(document.GetTitle() == "Title");

		document.Undo();
		REQUIRE(document.GetTitle() == "");

		document.Redo();
		REQUIRE(document.GetTitle() == "Title");
	}

	THEN("can add paragraph")
	{
		optional<size_t> index;
		TestInsertParagraph(document, "Paragraph 1", index);

		index = 0;
		TestInsertParagraph(document, "Paragraph 2", index);
	}

	THEN("can add image")
	{
		optional<size_t> index;
		REQUIRE(fs::exists(TEST_IMAGE));

		TestInsertImage(document, TEST_IMAGE, 800, 600, index);

		index = 0;
		TestInsertImage(document, TEST_IMAGE, 800, 600, index);
	}

	THEN("check insertion index")
	{
		REQUIRE_THROWS_AS(TestInsertParagraph(document, "Paragraph 1", 1), out_of_range);
	}

	THEN("adding image doesn't exist")
	{
		REQUIRE_THROWS_AS(TestInsertImage(document, ":/notexist.jpg", 800, 600, 0), logic_error);
	}

	THEN("can delete item")
	{
		TestInsertParagraph(document, "Paragraph 1", 0);

		document.DeleteItem(0);
		REQUIRE(document.GetItemsCount() == 0);

		document.Undo();
		REQUIRE(document.GetItemsCount() == 1);

		document.Redo();
		REQUIRE(document.GetItemsCount() == 0);
	}

	THEN("image item size check")
	{
		auto insert = [&](int width, int height) {
			document.InsertImage(TEST_IMAGE, width, height, 0);
		};

		REQUIRE_THROWS_AS(insert(0, 600), out_of_range);
		REQUIRE_THROWS_AS(insert(10001, 600), out_of_range);

		REQUIRE_THROWS_AS(insert(800, 0), out_of_range);
		REQUIRE_THROWS_AS(insert(800, 10001), out_of_range);
	}
}
	

	