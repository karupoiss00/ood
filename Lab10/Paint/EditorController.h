#pragma once
#include <functional>
#include <memory>
#include <QtWidgets>
#include <QColor>
#include <QPoint>
#include "Image.h"

class EditorView;
class EditorState;

class EditorController : public QObject
{
	Q_OBJECT
public:
	EditorController(EditorView* view, EditorState* state);

public slots:
	void ClearImageHandler();
	void SaveImageHandler();

private slots:
	void MouseDownHandler(QMouseEvent* event);
	void MouseMoveHandler(QMouseEvent* event);
	void MouseUpHandler(QMouseEvent* event);

private:
	EditorView* m_view;
	EditorState* m_state;

	bool m_drawing;
	QPoint m_lastPoint;
};