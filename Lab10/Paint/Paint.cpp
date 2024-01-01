#include <QtWidgets>

#include "Paint.h"
#include "ScribbleArea.h"

Paint::Paint()
{
	scribbleArea = new ScribbleArea;
	setCentralWidget(scribbleArea);

	CreateActions();
	CreateUI();

	setWindowTitle(tr("Paint"));
	resize(500, 500);
}

// User tried to close the app
void Paint::closeEvent(QCloseEvent* event)
{
	if (!HasUnsavedChanges())
	{
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

void Paint::OpenFileHandler()
{
	if (HasUnsavedChanges())
	{
		return;
	}

	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());

	if (fileName.isEmpty())
	{
		return;
	}

	scribbleArea->OpenImage(fileName);
}

void Paint::SaveFileHandler()
{
	QAction* action = qobject_cast<QAction*>(sender());

	QByteArray fileFormat = action->data().toByteArray();

	SaveFile(fileFormat);
}

void Paint::SetPenColorHandler()
{
	QColor newColor = QColorDialog::getColor(scribbleArea->GetPenColor());

	if (!newColor.isValid())
	{
		return;
	}

	scribbleArea->SetPenColor(newColor);
}


void Paint::SetPenWidthHandler()
{
	bool ok;

	int newWidth = QInputDialog::getInt(
		this, 
		tr("Scribble"),
		tr("Select pen width:"),
		scribbleArea->GetPenSize(),
		1, 50, 1, 
		&ok
	);

	if (ok)
	{
		scribbleArea->SetPenWidth(newWidth);
	}
		
}

void Paint::AboutHandler()
{
	QMessageBox::about(
		this,
		tr("About Scribble"),
		tr("<p>The <b>Scribble</b> example is awesome</p>")
	);
}

void Paint::CreateOpenFileAction()
{
	m_openFileAction = new QAction(tr("&Open..."), this);
	m_openFileAction->setShortcuts(QKeySequence::Open);
	connect(m_openFileAction, SIGNAL(triggered()), this, SLOT(OpenFileHandler()));
}
void Paint::CreateSaveFileAction()
{
	foreach (QByteArray format, QImageWriter::supportedImageFormats())
	{
		QString text = tr("%1...").arg(QString(format).toUpper());
		QAction* action = new QAction(text, this);
		action->setData(format);

		connect(action, SIGNAL(triggered()), this, SLOT(SaveFileHandler()));

		m_saveAsActions.append(action);
	}
}

void Paint::CreateChangePenColorAction()
{
	m_penColorChangeAction = new QAction(tr("&Pen Color..."), this);
	connect(m_penColorChangeAction, SIGNAL(triggered()), this, SLOT(SetPenColorHandler()));
}

void Paint::CreateChangePenSizeAction()
{
	m_penSizeChangeAction = new QAction(tr("Pen &Width..."), this);
	connect(m_penSizeChangeAction, SIGNAL(triggered()), this, SLOT(SetPenWidthHandler()));
}

void Paint::CreateOpenAboutAction()
{
	m_openAboutAction = new QAction(tr("&About"), this);
	connect(m_openAboutAction, SIGNAL(triggered()), this, SLOT(AboutHandler()));
}

void Paint::CreateOpenAboutFrameoworkAction()
{
	m_openAboutFrameworkAction = new QAction(tr("About &Qt"), this);
	connect(m_openAboutFrameworkAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}


void Paint::CreateExitAction()
{
	m_exitAction = new QAction(tr("E&xit"), this);
	m_exitAction->setShortcuts(QKeySequence::Quit);

	connect(m_exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void Paint::CreateClearScreenAction()
{
	m_clearScreenAction = new QAction(tr("&Clear Screen"), this);
	m_clearScreenAction->setShortcut(tr("Ctrl+L"));
	connect(m_clearScreenAction, SIGNAL(triggered()),
		scribbleArea, SLOT(clearImage()));
}

void Paint::CreateActions()
{
	CreateOpenFileAction();
	CreateSaveFileAction();
	CreateExitAction();
	CreateChangePenColorAction();
	CreateChangePenSizeAction();
	CreateClearScreenAction();
	CreateOpenAboutAction();
	CreateOpenAboutFrameoworkAction();
}


void Paint::CreateUI()
{
	saveAsMenu = new QMenu(tr("&Save As"), this);
	foreach (QAction* action, m_saveAsActions)
		saveAsMenu->addAction(action);

	fileMenu = new QMenu(tr("&File"), this);
	fileMenu->addAction(m_openFileAction);
	fileMenu->addMenu(saveAsMenu);
	fileMenu->addSeparator();
	fileMenu->addAction(m_exitAction);

	optionMenu = new QMenu(tr("&Options"), this);
	optionMenu->addAction(m_penColorChangeAction);
	optionMenu->addAction(m_penSizeChangeAction);
	optionMenu->addSeparator();
	optionMenu->addAction(m_clearScreenAction);

	helpMenu = new QMenu(tr("&Help"), this);
	helpMenu->addAction(m_openAboutAction);
	helpMenu->addAction(m_openAboutFrameworkAction);

	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(optionMenu);
	menuBar()->addMenu(helpMenu);
}

bool Paint::HasUnsavedChanges()
{
	if (!scribbleArea->IsModified())
	{
		return false;
	}

	QMessageBox::StandardButton ret;

	ret = QMessageBox::warning(this, tr("Scribble"),
		tr("The image has been modified.\n"
		   "Do you want to save your changes?"),
		QMessageBox::Save | QMessageBox::Discard
			| QMessageBox::Cancel);

	if (ret == QMessageBox::Save)
	{
		return SaveFile("png");
	}
	
	return false;
}

bool Paint::SaveFile(const QByteArray& fileFormat)
{
	QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;


	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
		initialPath,
		tr("%1 Files (*.%2);;All Files (*)")
			.arg(QString::fromLatin1(fileFormat.toUpper()))
			.arg(QString::fromLatin1(fileFormat)));

	if (fileName.isEmpty())
	{
		return false;
	}
	
	return scribbleArea->SaveImage(fileName, fileFormat.constData());
}