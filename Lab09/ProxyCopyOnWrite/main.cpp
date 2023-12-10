#include "Drawer.h"
#include <iostream>
#include <sstream>

using namespace std;

constexpr Color FIELD_LINE_COLOR = 'x';
constexpr Color CROSS_COLOR = 'o';
constexpr Color CIRCLE_COLOR = 'o';
constexpr Color WIN_LINE_COLOR = 'X';

constexpr int CIRCLE_PADDING = 1;

Image LoadImage(const std::string& pixels);
void Print(const Image& img, std::ostream& out);

void DrawGameCross(Image& image, Point center, int size, char color);
void DrawGameCircle(Image& image, Point center, int radius, char color);

int main()
{
	Image image({ 29, 29 }, '.');

	Print(image, cout);
	cout << Tile::GetInstanceCount() << endl;

	DrawLine(image, { 9, 0 }, { 9, 28 }, FIELD_LINE_COLOR);
	DrawLine(image, { 19, 0 }, { 19, 28 }, FIELD_LINE_COLOR);
	DrawLine(image, { 0, 9 }, { 29, 9 }, FIELD_LINE_COLOR);
	DrawLine(image, { 0, 19 }, { 29, 19 }, FIELD_LINE_COLOR);

	DrawGameCircle(image, { 14, 14 }, 4, CIRCLE_COLOR);

	DrawGameCircle(image, { 24, 4 }, 4, CIRCLE_COLOR);

	DrawGameCross(image, { 4, 4 }, 8, CROSS_COLOR);

	DrawGameCross(image, { 4, 14 }, 8, CROSS_COLOR);

	DrawGameCross(image, { 4, 14 }, 8, CROSS_COLOR);

	DrawGameCross(image, { 4, 24 }, 8, CROSS_COLOR);

	DrawLine(image, { 4, 0 }, { 4, 28 }, WIN_LINE_COLOR);

	Print(image, cout);

	cout << Tile::GetInstanceCount() << endl;

	return 0;
}

/**
 * Выводит в поток out изображение в виде символов.
 */
void Print(const Image& img, std::ostream& out)
{
	const auto size = img.GetSize();
	for (int y = 0; y < size.height; ++y)
	{
		for (int x = 0; x < size.width; ++x)
		{
			out.put(img.GetPixel({ x, y }));
			out.put(' ');
		}
		out.put('\n');
	}
}

/**
 * Загружает изображение из pixels. Линии изображения разделяются символами \n.
 * Размеры картинки определяются по количеству переводов строки и самой длинной линии.
 */
Image LoadImage(const std::string& pixels)
{
	std::istringstream s(pixels);
	Size size;
	std::string line;
	while (std::getline(s, line))
	{
		size.width = std::max(size.width, static_cast<int>(line.length()));
		++size.height;
	}

	Image img(size);

	s = std::istringstream(pixels);
	for (int y = 0; y < size.height; ++y)
	{
		if (!std::getline(s, line))
			break;

		int x = 0;
		for (char ch : line)
		{
			img.SetPixel({ x++, y }, ch);
		}
	}

	return img;
}

void DrawGameCross(Image& image, Point center, int size, char color)
{
	DrawLine(image, { center.x - size / 2, center.y - size / 2 }, { center.x + size / 2, center.y + size / 2 }, color);
	DrawLine(image, { center.x + size / 2, center.y - size / 2 }, { center.x - size / 2, center.y + size / 2 }, color);
}

void DrawGameCircle(Image& image, Point center, int radius, char color)
{
	DrawCircle(image, center, radius, CIRCLE_COLOR);
	FillCircle(image, center, radius - CIRCLE_PADDING * 2, CIRCLE_COLOR);
}