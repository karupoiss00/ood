#pragma once
#include "SaverPPM.h"
#include "Image.h"

class ImagePPMAdapter : public IImage
{
public:
	ImagePPMAdapter(Image& img)
		: m_img(img)
	{}

	Size GetSize() const override
	{
		return m_img.GetSize();
	}

	RGBColor GetPixelColor(Point p) const override
	{
		Color color = m_img.GetPixel(p);

		auto red = (color >> 16) & 0xFF;
		auto green = (color >> 8) & 0xFF;
		auto blue = color & 0xFF; 

		return {
			red,
			green,
			blue
		};
	}

private:
	Image& m_img;
};