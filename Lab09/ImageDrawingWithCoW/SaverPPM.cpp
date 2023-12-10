#include <fstream>
#include "SaverPPM.h"

using namespace std;

SaverPPM::SaverPPM(IImage& img)
	: m_image(img)
{
}

void SaverPPM::Save(string const& fileName) const
{
	ofstream outputFile(fileName);

	Size sz = m_image.GetSize();
	int width = sz.width;
	int height = sz.height;

	outputFile << "P3" << endl;
	outputFile << width << " " << height << endl;
	outputFile << 255 << endl;

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			RGBColor pixelColor = m_image.GetPixelColor({x, y});
			outputFile << pixelColor.r << ' '
				<< pixelColor.g << ' '
				<< pixelColor.b << ' '
				<< endl;
		}
	}

	outputFile.close();
}