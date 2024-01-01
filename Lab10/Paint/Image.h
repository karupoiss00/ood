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
	explicit Image(Size size, Color color = 0x000000);

	Size GetSize() const noexcept;

	Color GetPixel(Point p) const noexcept;

	void SetPixel(Point p, Color color);

private:
	CoW<Tile> const& GetTile(Point const& p) const;
	CoW<Tile>& GetTile(Point const& p);

	std::vector<std::vector<CoW<Tile>>> m_tiles;
	Size m_size;
};