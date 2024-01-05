#pragma once
#include <QtWidgets/QMainWindow>
#include <QList>

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Document;
class EditorState;
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

	bool HasUnsavedChanges();

	bool SaveFile(const QByteArray& fileFormat);

	Document* m_document;
	EditorState* m_editorState;
	EditorView* m_editorView;
	EditorController* m_editorController;

	QMenu* m_saveAsMenu;
	QMenu* m_fileMenu;
	QMenu* m_optionMenu;
	QMenu* m_helpMenu;

	QAction* m_openFileAction;

	QList<QAction*> m_saveAsActions;
	QAction* m_exitAction;
	QAction* m_penColorChangeAction;
	QAction* m_penSizeChangeAction;
	QAction* printAct;
	QAction* m_clearScreenAction;
	QAction* m_openAboutAction;
	QAction* m_openAboutFrameworkAction;
};

#endif