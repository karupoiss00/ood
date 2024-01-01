#pragma once
#include <QtWidgets/QMainWindow>
#include <QList>

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class ScribbleArea;

class Paint : public QMainWindow
{
	Q_OBJECT

public:
	Paint();

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
	void CreateSaveFileAction();
	void CreateExitAction();
	void CreateClearScreenAction();
	void CreateChangePenColorAction();
	void CreateChangePenSizeAction();
	void CreateOpenAboutAction();
	void CreateOpenAboutFrameoworkAction();

	bool HasUnsavedChanges();

	bool SaveFile(const QByteArray& fileFormat);

	ScribbleArea* scribbleArea;

	QMenu* saveAsMenu;
	QMenu* fileMenu;
	QMenu* optionMenu;
	QMenu* helpMenu;


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