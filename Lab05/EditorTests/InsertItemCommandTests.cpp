#include <boost/filesystem.hpp>
#include <optional>
#include <catch2/catch.hpp>
#include "InsertItemCommand.h"
#include "DocumentItem.h"
#include "Image.h"
#include "MockHistoryController.h"

using namespace std;
namespace fs = boost::filesystem;

const string TEST_IMAGE = fs::current_path().string() + "\\mock_data\\test.bmp";
const string TEMP_FOLDER = fs::current_path().string() + "\\tmp";
const string TEMP_IMAGE = TEMP_FOLDER + "\\test.bmp";

struct AddItemCommandFixture
{
	AddItemCommandFixture()
	{
		if (fs::exists(TEMP_FOLDER))
		{
			fs::remove_all(TEMP_FOLDER);
		}

		fs::create_directory(TEMP_FOLDER);
		fs::copy_file(TEST_IMAGE, TEMP_IMAGE);
	}

	~AddItemCommandFixture()
	{
		fs::remove_all(TEMP_FOLDER);
	}
};

TEST_CASE_METHOD(AddItemCommandFixture, "check resource cleaning, when command wasn't executed")
{
	CMockHistoryController historyController;
	std::vector<std::shared_ptr<CDocumentItem>> m_items;

	auto image = make_shared<CImage>(TEMP_IMAGE, 800, 600, historyController);
	auto item = make_shared<CDocumentItem>(image);

	auto command = new CInsertItemCommand(m_items, item, 0);
	delete command;

	REQUIRE(!fs::exists(TEMP_IMAGE));
}
