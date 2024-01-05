#pragma once
#include <QWidget>

class IDrawingStrategy
{
public:
	virtual void OnMouseDown(QMouseEvent* event) = 0;
	virtual void OnMouseMove(QMouseEvent* event) = 0;
	virtual void OnMouseUp(QMouseEvent* event) = 0;
};