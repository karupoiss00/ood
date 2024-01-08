#pragma once
#include <QAction>

class EditorController;

class ToolsMenuController : public QObject
{
	Q_OBJECT
public:
	ToolsMenuController(QWidget* parent, EditorController* controller);

	QMenu* View();

	~ToolsMenuController();

private slots:
	void DrawColorChangeHandler();
	void DrawSizeChangeHandler();
	void ClearImageHandler();

private:
	void InitSetDrawSizeAction();
	void InitSetDrawColorAction();
	void InitClearScreenAction();

	void CreateView();

	QMenu* m_view;

	QAction* m_drawColorChangeAction;
	QAction* m_drawSizeChangeAction;
	QAction* m_clearScreenAction;

	EditorController* m_editorController;

	QWidget* m_parent;
};