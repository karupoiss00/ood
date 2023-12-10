#pragma once
#include <iosfwd>
#include <string>
#include <vector>

#include "Geometry.h"
#include "CoW.h"
#include "Tile.h"
#include "Color.h"

class Image
{
public:
	explicit Image(Size size, Color color = ' ');

	Size GetSize() const noexcept;

	char GetPixel(Point p) const noexcept;

	void SetPixel(Point p, Color color);

private:
	CoW<Tile> const& GetTile(Point const& p) const;
	CoW<Tile>& GetTile(Point const& p);

	std::vector<std::vector<CoW<Tile>>> m_tiles;
	Size m_size;
};