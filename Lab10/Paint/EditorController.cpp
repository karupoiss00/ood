#include "EditorView.h"
#include "EditorController.h"
#include "EditorState.h"
#include "Drawer.h"

EditorController::EditorController(EditorView* view, EditorState* state)
	: m_view(view)
	, m_state(state)
{
	connect(m_view, &EditorView::MouseDownEvent, this, &EditorController::MouseDownHandler);
	connect(m_view, &EditorView::MouseMoveEvent, this, &EditorController::MouseMoveHandler);
	connect(m_view, &EditorView::MouseUpEvent, this, &EditorController::MouseUpHandler);
}


void EditorController::ClearImageHandler()
{
	m_state->GetDocument().SetImage(Image());
}

void EditorController::MouseDownHandler(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_drawing = true;
		m_lastPoint = event->pos();
	}
}

void EditorController::MouseMoveHandler(QMouseEvent* event)
{
	if (!m_drawing)
	{
		return;
	}

	if (event->buttons() & Qt::LeftButton)
	{
		auto document = m_state->GetDocument();
		auto penSize = m_state->GetPenSize();
		auto penColor = m_state->GetPenColor();

		auto pos = event->pos();
		auto radius = (penSize / 2) + 2;
		DrawLine(*document.GetEditableImage(), { m_lastPoint.x(), m_lastPoint.y() }, { pos.x(), pos.y() }, penColor.rgb(), penSize);

		auto dirtyRect = QRect(m_lastPoint, pos).normalized().adjusted(-radius, -radius, +radius, +radius);

		m_view->update(dirtyRect);
		m_lastPoint = pos;
	}
}

void EditorController::MouseUpHandler(QMouseEvent* event)
{
	m_drawing = false;
}

void EditorController::SaveImageHandler()
{
	m_state->SaveChanges();
}