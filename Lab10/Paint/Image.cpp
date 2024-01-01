#include <cassert>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "Image.h"

using namespace std;

Image::Image(Size size, Color color)
	: m_size(move(size))
{
	size_t tilesHorizontalCount = size.width / Tile::SIZE + (size.width % Tile::SIZE != 0);
	size_t tilesVerticalCount = size.height / Tile::SIZE + (size.height % Tile::SIZE != 0);
	
	CoW<Tile> filledTile(color);
	
	m_tiles = vector<vector<CoW<Tile>>>(
		tilesVerticalCount,
		vector<CoW<Tile>>(tilesHorizontalCount, filledTile)
	);
}

Size Image::GetSize() const noexcept
{
	return m_size;
}

Color Image::GetPixel(Point p) const noexcept
{
	try 
	{
		auto tile = GetTile(p);
		int relativeX = p.x % Tile::SIZE;
		int relativeY = p.y % Tile::SIZE;

		return tile->GetPixel({ relativeX, relativeY });
	}
	catch (...)
	{}

	return ' ';
}

void Image::SetPixel(Point p, Color color)
{
	try
	{
		auto& tile = GetTile(p);
		int relativeX = p.x % Tile::SIZE;
		int relativeY = p.y % Tile::SIZE;

		tile--->SetPixel({ relativeX, relativeY }, color);
	}
	catch (...) {}
}


CoW<Tile>& Image::GetTile(Point const& p)
{
	if (p.x >= m_size.width || p.y >= m_size.height)
	{
		throw std::out_of_range("tile y out of range");
	}

	unsigned tileX = static_cast<unsigned>(p.x / Tile::SIZE);
	unsigned tileY = static_cast<unsigned>(p.y / Tile::SIZE);

	return m_tiles[tileY][tileX];
}

CoW<Tile> const& Image::GetTile(Point const& p) const
{
	if (p.x >= m_size.width || p.y >= m_size.height)
	{
		throw std::out_of_range("tile y out of range");
	}

	unsigned tileX = static_cast<unsigned>(p.x / Tile::SIZE);
	unsigned tileY = static_cast<unsigned>(p.y / Tile::SIZE);

	return m_tiles[tileY][tileX];
}
