#include "ToolsMenuController.h"
#include "EditorController.h"

ToolsMenuController::ToolsMenuController(QWidget* parent, EditorController* controller)
	: m_editorController(controller)
	, m_parent(parent)
{
	InitSetDrawColorAction();
	InitSetDrawSizeAction();
	InitClearScreenAction();

	CreateView();
}

ToolsMenuController::~ToolsMenuController()
{
	delete m_view;
	delete m_drawColorChangeAction;
	delete m_drawSizeChangeAction;
	delete m_clearScreenAction;
}

void ToolsMenuController::CreateView()
{
	m_view = new QMenu(tr("&Options"), m_parent);
	m_view->addAction(m_drawColorChangeAction);
	m_view->addAction(m_drawSizeChangeAction);
	m_view->addSeparator();
	m_view->addAction(m_clearScreenAction);
}

void ToolsMenuController::InitSetDrawColorAction()
{
	m_drawColorChangeAction = new QAction(tr("&Draw Color..."), this);
	connect(m_drawColorChangeAction, SIGNAL(triggered()), this, SLOT(DrawColorChangeHandler()));
}

void ToolsMenuController::InitSetDrawSizeAction()
{
	m_drawSizeChangeAction = new QAction(tr("Draw &Size..."), this);
	connect(m_drawSizeChangeAction, SIGNAL(triggered()), this, SLOT(DrawSizeChangeHandler()));
}

void ToolsMenuController::InitClearScreenAction()
{
	m_clearScreenAction = new QAction(tr("&Clear Screen"), this);
	m_clearScreenAction->setShortcut(tr("Ctrl+L"));
	connect(m_clearScreenAction, SIGNAL(triggered()), this, SLOT(ClearImageHandler()));
}

void ToolsMenuController::DrawColorChangeHandler()
{
	auto drawingSettings = m_editorController->GetDrawingSettings();
	QColor newColor = QColorDialog::getColor(drawingSettings.color);

	if (!newColor.isValid())
	{
		return;
	}

	m_editorController->SetDrawingColor(newColor);
}

void ToolsMenuController::DrawSizeChangeHandler()
{
	auto drawingSettings = m_editorController->GetDrawingSettings();
	bool ok;

	int newSize = QInputDialog::getInt(
		m_parent,
		tr("Size"),
		tr("Select draw size:"),
		drawingSettings.size,
		1, 50, 1,
		&ok);

	if (ok)
	{
		m_editorController->SetDrawingSize(newSize);
	}
}

void ToolsMenuController::ClearImageHandler()
{
	m_editorController->ClearImage();
}

QMenu* ToolsMenuController::View()
{
	return m_view;
}