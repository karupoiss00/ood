#pragma once
#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include "Document.h"

class EditorView : public QWidget
{
	Q_OBJECT

public:
	EditorView(QWidget* parent, Document* document);

	void SetDocument(Document* image);
signals:
	void MouseDownEvent(QMouseEvent* event);
	void MouseMoveEvent(QMouseEvent* event);
	void MouseUpEvent(QMouseEvent* event);

protected:
	void paintEvent(QPaintEvent* event) override;

	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	Document* m_document;
};

#endif