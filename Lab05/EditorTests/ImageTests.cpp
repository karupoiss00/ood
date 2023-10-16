#include <catch2/catch.hpp>
#include "Image.h"
#include "MockHistoryController.h"

using namespace std;

const string IMAGE_PATH = "D:\\C++\\oop\\cpp.jpg";
const int IMAGE_WIDTH = 200;
const int IMAGE_HEIGHT = 100;

struct ImageFixture
{
	ImageFixture()
		: image(IMAGE_PATH, IMAGE_WIDTH, IMAGE_HEIGHT, historyController){};

	CMockHistoryController historyController;
	CImage image;
};

TEST_CASE_METHOD(ImageFixture, "Image")
{
	WHEN("created")
	{
		THEN("has path")
		{
			REQUIRE(image.GetPath() == IMAGE_PATH);
		}

		THEN("has width and height")
		{
			REQUIRE(image.GetWidth() == IMAGE_WIDTH);
			REQUIRE(image.GetHeight() == IMAGE_HEIGHT);
		}
	}

	SECTION("undo/redo")
	{
		image.Resize(100, 200);
		REQUIRE(image.GetWidth() == 100);
		REQUIRE(image.GetHeight() == 200);

		historyController.Undo();
		REQUIRE(image.GetWidth() == IMAGE_WIDTH);
		REQUIRE(image.GetHeight() == IMAGE_HEIGHT);

		historyController.Redo();

		REQUIRE(image.GetWidth() == 100);
		REQUIRE(image.GetHeight() == 200);
	}
}
	