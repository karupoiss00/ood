#pragma once

#include <array>
#include <cassert>

#include "Color.h"
#include "Geometry.h"

class Tile
{
public:
	constexpr static int SIZE = 8;

	Tile(Color color = ' ') noexcept;
	Tile(const Tile& other);
	~Tile();

	void SetPixel(Point p, Color color) noexcept;
	char GetPixel(Point p) const noexcept;

	static int GetInstanceCount() noexcept;

private:
	bool IsValidPoint(Point const& p) const;

	inline static int m_instanceCount = 0;
	std::array<std::array<Color, SIZE>, SIZE> m_pixels;
};