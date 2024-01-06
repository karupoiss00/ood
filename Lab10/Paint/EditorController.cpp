#include "EditorView.h"
#include "EditorController.h"
#include "Editor.h"
#include "Drawer.h"

EditorController::EditorController(EditorView* view, Editor* state)
	: m_view(view)
	, m_state(state)
{
	connect(m_view, &EditorView::MouseDownEvent, this, &EditorController::MouseDownHandler);
	connect(m_view, &EditorView::MouseMoveEvent, this, &EditorController::MouseMoveHandler);
	connect(m_view, &EditorView::MouseUpEvent, this, &EditorController::MouseUpHandler);
}

void EditorController::ClearImageHandler()
{
	m_state->ClearImage();
	m_view->update();
}

void EditorController::MouseDownHandler(QMouseEvent* event)
{
	m_state->StartPaint(event);
}

void EditorController::MouseMoveHandler(QMouseEvent* event)
{
	m_state->Paint(event);
}

void EditorController::MouseUpHandler(QMouseEvent* event)
{
	m_state->EndPaint(event);
}

void EditorController::SaveImageHandler()
{
	m_state->SaveChanges();
}