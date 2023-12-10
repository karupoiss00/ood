#include <iostream>
#include <sstream>
#include "Drawer.h"

using namespace std;

Image LoadImage(const std::string& pixels);
void Print(const Image& img, std::ostream& out);

int main()
{
	Image image({ 30, 30 }, '.');

	Print(image, cout);
	cout << Tile::GetInstanceCount() << endl;
	
	DrawLine(image, { 9, 0 }, { 9, 29 }, 'x');
	DrawLine(image, { 19, 0 }, { 19, 29 }, 'x');
	DrawLine(image, { 0, 9 }, { 29, 9 }, 'x');
	DrawLine(image, { 0, 19 }, { 29, 19 }, 'x');

	DrawCircle(image, { 14, 14 }, 4, 'o');

	FillCircle(image, { 25, 4 }, 4, 'o');

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
