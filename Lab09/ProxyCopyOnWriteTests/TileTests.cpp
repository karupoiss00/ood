#include <catch2/catch.hpp>
#include "Tile.h"

TEST_CASE("Tile initialization", "[Tile]")
{
	Tile tile('A');

	SECTION("Check default color and instance count")
	{
		REQUIRE(tile.GetPixel({ 0, 0 }) == 'A');
		REQUIRE(Tile::GetInstanceCount() == 1);
	}

	SECTION("Check pixel setting")
	{
		tile.SetPixel({ 1, 1 }, 'B');
		REQUIRE(tile.GetPixel({ 1, 1 }) == 'B');
	}
}

TEST_CASE("Tile copy constructor", "[Tile]")
{
	Tile originalTile('A');
	Tile copyTile(originalTile);

	SECTION("Check copied pixels and instance count")
	{
		REQUIRE(copyTile.GetPixel({ 0, 0 }) == 'A');
		REQUIRE(Tile::GetInstanceCount() == 2);
	}

	SECTION("Check changing original does not affect copy")
	{
		originalTile.SetPixel({ 1, 1 }, 'B');
		REQUIRE(copyTile.GetPixel({ 1, 1 }) == 'A');
	}
}

TEST_CASE("Tile destructor", "[Tile]")
{
	{
		Tile tile('A');
		REQUIRE(Tile::GetInstanceCount() == 1);
	}

	REQUIRE(Tile::GetInstanceCount() == 0);
}

TEST_CASE("Tile pixel access out of bounds", "[Tile]")
{
	Tile tile('A');

	SECTION("Check out of bounds pixel setting")
	{
		tile.SetPixel({ Tile::SIZE, Tile::SIZE }, 'B');
		REQUIRE(tile.GetPixel({ Tile::SIZE, Tile::SIZE }) == ' ');
	}

	SECTION("Check out of bounds pixel getting")
	{
		REQUIRE(tile.GetPixel({ Tile::SIZE, Tile::SIZE }) == ' ');
	}
}