#pragma once
#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

class ScribbleArea : public QWidget
{
	Q_OBJECT

public:
	ScribbleArea(QWidget* parent = 0);

	bool OpenImage(const QString& fileName);
	bool SaveImage(const QString& fileName, const char* fileFormat);
	void SetPenColor(const QColor& newColor);
	void SetPenWidth(int newWidth);

	bool IsModified() const { return m_imageModified; }
	QColor GetPenColor() const { return m_penColor; }
	int GetPenSize() const { return m_penSize; }

public slots:
	void ClearImage();

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

	void paintEvent(QPaintEvent* event) override;

	void resizeEvent(QResizeEvent* event) override;

private:
	void DrawLineTo(const QPoint& endPoint);
	void ResizeImage(QImage* image, const QSize& newSize);

	bool m_imageModified;
	bool m_drawing;
	int m_penSize;
	QColor m_penColor;
	QImage m_image;

	QPoint m_lastPoint;
};

#endif