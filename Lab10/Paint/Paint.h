#pragma once
#include <memory>
#include <optional>
#include <QtWidgets/QMainWindow>
#include <QList>

#include "DrawingStrategyFactory.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Image;
class Editor;
class EditorView;
class EditorController;

class Paint : public QMainWindow
{
	Q_OBJECT

public:
	Paint();
	~Paint();

protected:
	void closeEvent(QCloseEvent* event) override;

private slots:
	void OpenFileHandler();
	void SaveFileHandler();
	void SetPenColorHandler();
	void SetPenWidthHandler();
	void AboutHandler();

private:
	void CreateActions();
	void CreateUI();

	void CreateOpenFileAction();
	void CreateExitAction();
	void CreateClearScreenAction();
	void CreateChangePenColorAction();
	void CreateChangePenSizeAction();
	void CreateOpenAboutAction();
	void CreateOpenAboutFrameoworkAction();
	void CreateSaveFileAction();

	std::optional<bool> HasUnsavedChanges();

	bool SaveFile(const QByteArray& fileFormat);

	std::shared_ptr<Image> m_image;

	DrawingStrategyFactory m_drawingStrategyFactory;
	Editor* m_editor;
	EditorController* m_editorController;
	EditorView* m_editorView;

	QMenu* m_saveAsMenu;
	QMenu* m_fileMenu;
	QMenu* m_optionMenu;
	QMenu* m_helpMenu;

	QAction* m_openFileAction;

	QList<QAction*> m_saveAsActions;
	QAction* m_exitAction;
	QAction* m_penColorChangeAction;
	QAction* m_penSizeChangeAction;
	QAction* m_clearScreenAction;
	QAction* m_openAboutAction;
	QAction* m_openAboutFrameworkAction;
};

#endif