#include <catch2/catch.hpp>
#include "Image.h"

TEST_CASE("Image initialization", "[Image]")
{
	Image image({ 100, 50 }, '*');

	SECTION("Check size") 
	{
		REQUIRE(image.GetSize().width == 100);
		REQUIRE(image.GetSize().height == 50);
	}

	SECTION("Check default color and instance count")
	{
		REQUIRE(image.GetPixel({ 0, 0 }) == '*');
		REQUIRE(Tile::GetInstanceCount() == 1);
	}

	SECTION("Check pixel setting")
	{
		image.SetPixel({ 1, 1 }, 'B');
		REQUIRE(image.GetPixel({ 1, 1 }) == 'B');

		REQUIRE(Tile::GetInstanceCount() == 2);

		SECTION("Check changing unique tile not instance new tile")
		{
			image.SetPixel({ Tile::SIZE - 1, Tile::SIZE - 1 }, 'A');
			REQUIRE(image.GetPixel({ Tile::SIZE - 1, Tile::SIZE - 1 }) == 'A');
			REQUIRE(Tile::GetInstanceCount() == 2);
		}
	}
}

TEST_CASE("Image pixel access out of bounds", "[Image]")
{
	Image image({ 100, 50 }, '*');

	SECTION("Check out of bounds pixel setting")
	{
		image.SetPixel({ 100, 50 }, 'B');
		REQUIRE(image.GetPixel({ 100, 50 }) == ' ');
	}

	SECTION("Check out of bounds pixel getting")
	{
		REQUIRE(image.GetPixel({ 100, 50 }) == ' ');
	}
}