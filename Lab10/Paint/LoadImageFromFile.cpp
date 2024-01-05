#include <QImage>
#include "LoadImageFromFile.h"
#include "QImageToImage.h"

Image LoadImageFromFile(QString fileName)
{
	QImage loadedImage;

	if (!loadedImage.load(fileName))
	{
		return Image();
	}

	return createImageFromQImage(loadedImage);
}