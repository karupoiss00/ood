#pragma once
#include <iostream>
#include "Geometry.h"

struct RGBColor
{
	unsigned r, g, b;
};

struct IImage
{
	virtual Size GetSize() const = 0;
	virtual RGBColor GetPixelColor(Point p) const = 0;
};

class SaverPPM
{
public:
	SaverPPM(IImage& img);
	void Save(std::string const& fileName) const;

private:
	IImage& m_image;
};