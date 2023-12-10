#include <iostream>
#include <sstream>
#include <fstream>

#include "Drawer.h"
#include "SaverPPM.h"
#include "ImagePPMAdapter.h"

using namespace std;

constexpr Color BACKGROUND_COLOR = 0xE6D4B1;
constexpr Color FIELD_LINE_COLOR = 0x161915;
constexpr Color CROSS_COLOR = 0xE3584D;
constexpr Color CIRCLE_COLOR = 0x6FE078;
constexpr Color WIN_LINE_COLOR = 0xFFCD3B;

constexpr int CIRCLE_PADDING = 1;

void DrawGameCross(Image& image, Point center, int size, Color color);
void DrawGameCircle(Image& image, Point center, int radius, Color color);
Image CreateImage();

int main()
{
	Image image = CreateImage();
	ImagePPMAdapter ppmAdaptedImage(image);
	SaverPPM ppm(ppmAdaptedImage);

	ppm.Save("output.ppm");

	return 0;
}

void DrawGameCross(Image& image, Point center, int size, Color color)
{
	DrawLine(image, { center.x - size / 2, center.y - size / 2 }, { center.x + size / 2, center.y + size / 2 }, color);
	DrawLine(image, { center.x + size / 2, center.y - size / 2 }, { center.x - size / 2, center.y + size / 2 }, color);
}

void DrawGameCircle(Image& image, Point center, int radius, Color color)
{
	DrawCircle(image, center, radius, CIRCLE_COLOR);
	FillCircle(image, center, radius - CIRCLE_PADDING * 2, CIRCLE_COLOR);
}

Image CreateImage() 
{
	Image image({ 29, 29 }, BACKGROUND_COLOR);

	cout << "before draw: " << Tile::GetInstanceCount() << endl;

	DrawLine(image, { 9, 0 }, { 9, 28 }, FIELD_LINE_COLOR);
	DrawLine(image, { 19, 0 }, { 19, 28 }, FIELD_LINE_COLOR);
	DrawLine(image, { 0, 9 }, { 29, 9 }, FIELD_LINE_COLOR);
	DrawLine(image, { 0, 19 }, { 29, 19 }, FIELD_LINE_COLOR);

	DrawGameCross(image, { 4, 4 }, 8, CROSS_COLOR);
	DrawGameCircle(image, { 14, 14 }, 4, CIRCLE_COLOR);
	DrawGameCross(image, { 4, 14 }, 8, CROSS_COLOR);
	DrawGameCircle(image, { 24, 4 }, 4, CIRCLE_COLOR);
	DrawGameCross(image, { 4, 24 }, 8, CROSS_COLOR);

	DrawLine(image, { 4, 0 }, { 4, 28 }, WIN_LINE_COLOR);

	cout << "after draw: " << Tile::GetInstanceCount() << endl;

	return image;
}