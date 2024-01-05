#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include "EditorView.h"
#include "QImageToImage.h"

EditorView::EditorView(QWidget* parent, Document* document)
	: QWidget(parent)
	, m_document(document)
{
	setAttribute(Qt::WA_StaticContents);
}

void EditorView::SetDocument(Document* document)
{
	m_document = document;
}

void EditorView::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	if (m_document == nullptr)
	{
		return;
	}

	QRect dirtyRect = event->rect();
	auto image = m_document->GetImage();
	painter.drawImage(dirtyRect, createQImageFromImage(image), dirtyRect);
}

void EditorView::mousePressEvent(QMouseEvent* event)
{
	emit MouseDownEvent(event);
}

void EditorView::mouseMoveEvent(QMouseEvent* event) 
{
	emit MouseMoveEvent(event);
}

void EditorView::mouseReleaseEvent(QMouseEvent* event)
{
	emit MouseUpEvent(event);
}