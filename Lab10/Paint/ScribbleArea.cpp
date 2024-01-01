#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#include <QPrinter>
#endif
#endif

#include "ScribbleArea.h"

ScribbleArea::ScribbleArea(QWidget* parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_StaticContents);

	m_imageModified = false;
	m_drawing = false;
	m_penSize = 1;
	m_penColor = Qt::blue;
}

bool ScribbleArea::OpenImage(const QString& fileName)
{
	QImage loadedImage;

	if (!loadedImage.load(fileName)) 
	{
		return false;
	}
		

	QSize newSize = loadedImage.size().expandedTo(size());
	ResizeImage(&loadedImage, newSize);
	m_image = loadedImage;
	m_imageModified = false;

	update();

	return true;
}

// Save the current image
bool ScribbleArea::SaveImage(const QString& fileName, const char* fileFormat)
{
	// Created to hold the image
	QImage visibleImage = m_image;
	ResizeImage(&visibleImage, size());

	if (visibleImage.save(fileName, fileFormat))
	{
		m_imageModified = false;
		return true;
	}
	else
	{
		return false;
	}
}

void ScribbleArea::SetPenColor(const QColor& newColor)
{
	m_penColor = newColor;
}

void ScribbleArea::SetPenWidth(int newWidth)
{
	m_penSize = newWidth;
}

void ScribbleArea::ClearImage()
{
	m_image.fill(qRgb(255, 255, 255));
	m_imageModified = true;
	update();
}

void ScribbleArea::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_lastPoint = event->pos();
		m_drawing = true;
	}
}

void ScribbleArea::mouseMoveEvent(QMouseEvent* event)
{
	if ((event->buttons() & Qt::LeftButton) && m_drawing)
	{
		DrawLineTo(event->pos());
	}
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton && m_drawing)
	{
		DrawLineTo(event->pos());
		m_drawing = false;
	}
}

void ScribbleArea::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	QRect dirtyRect = event->rect();

	painter.drawImage(dirtyRect, m_image, dirtyRect);
}

void ScribbleArea::resizeEvent(QResizeEvent* event)
{
	if (width() > m_image.width() || height() > m_image.height())
	{
		int newWidth = qMax(width() + 128, m_image.width());
		int newHeight = qMax(height() + 128, m_image.height());
		ResizeImage(&m_image, QSize(newWidth, newHeight));
		update();
	}
	QWidget::resizeEvent(event);
}

void ScribbleArea::DrawLineTo(const QPoint& endPoint)
{
	QPainter painter(&m_image);

	painter.setPen(
		QPen(
			m_penColor, 
			m_penSize, 
			Qt::SolidLine, 
			Qt::RoundCap,
			Qt::RoundJoin
		)
	);

	painter.drawLine(m_lastPoint, endPoint);

	m_imageModified = true;

	int rad = (m_penSize / 2) + 2;

	update(QRect(m_lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));

	m_lastPoint = endPoint;
}

void ScribbleArea::ResizeImage(QImage* image, const QSize& newSize)
{
	if (image->size() == newSize)
	{
		return;
	}

	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));

	QPainter painter(&newImage);
	painter.drawImage(QPoint(0, 0), *image);
	*image = newImage;
}