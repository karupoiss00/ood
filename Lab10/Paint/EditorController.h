#pragma once
#include <functional>
#include <memory>
#include <QtWidgets>
#include <QColor>
#include <QPoint>
#include "Image.h"

class EditorView;
class Editor;

class EditorController : public QObject
{
	Q_OBJECT
public:
	EditorController(EditorView* view, Editor* state);

public slots:
	void ClearImageHandler();
	void SaveImageHandler();

private slots:
	void MouseDownHandler(QMouseEvent* event);
	void MouseMoveHandler(QMouseEvent* event);
	void MouseUpHandler(QMouseEvent* event);

private:
	EditorView* m_view;
	Editor* m_state;
};