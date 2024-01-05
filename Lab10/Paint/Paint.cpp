#include <QtWidgets>
#include <string>

#include "Paint.h"
#include "Document.h"
#include "EditorState.h"
#include "EditorView.h"
#include "EditorController.h"
#include "LoadImageFromFile.h"
#include "QImageToImage.h"

const QByteArray DEFAULT_SAVE_FORMAT = "png";

Paint::Paint()
{
	m_document = new Document();
	m_editorState = new EditorState();
	m_editorView = new EditorView(this, m_document);
	m_editorController = new EditorController(m_editorView, m_editorState);

	setCentralWidget(m_editorView);

	CreateActions();
	CreateUI();

	setWindowTitle(tr("Paint"));

	auto size = m_document->GetImage().GetSize();

	resize(size.width, size.height);
}

Paint::~Paint()
{
	delete m_editorController;
	delete m_editorView;
	delete m_editorState;
	delete m_document;
	delete m_saveAsMenu;
	delete m_fileMenu;
	delete m_optionMenu;
	delete m_helpMenu;

	delete m_openFileAction;

	for (auto saveAction : m_saveAsActions)
	{
		delete saveAction;
	}

	delete m_exitAction;
	delete m_penColorChangeAction;
	delete m_penSizeChangeAction;
	delete printAct;
	delete m_clearScreenAction;
	delete m_openAboutAction;
	delete m_openAboutFrameworkAction;
}

void Paint::closeEvent(QCloseEvent* event)
{
	HasUnsavedChanges();

	event->accept();
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

	auto loadedImage = LoadImageFromFile(fileName);
	m_document->SetImage(loadedImage);
	m_editorView->update();
}

void Paint::SaveFileHandler()
{
	QAction* action = qobject_cast<QAction*>(sender());

	QByteArray fileFormat = action->data().toByteArray();

	SaveFile(fileFormat);
}

void Paint::SetPenColorHandler()
{
	QColor newColor = QColorDialog::getColor(m_editorState->GetPenColor());

	if (!newColor.isValid())
	{
		return;
	}

	m_editorState->SetPenColor(newColor);
}


void Paint::SetPenWidthHandler()
{
	bool ok;

	int newWidth = QInputDialog::getInt(
		this, 
		tr("Scribble"),
		tr("Select pen width:"),
		m_editorState->GetPenSize(),
		1, 50, 1, 
		&ok
	);

	if (ok)
	{
		m_editorState->SetPenSize(newWidth);
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
	for (auto& format : QImageWriter::supportedImageFormats())
	{
		QString text = tr("%1...").arg(QString(format).toUpper());
		QAction* action = new QAction(text, this);
		action->setData(format);

		connect(action, SIGNAL(triggered()), this, SLOT(SaveFileHandler()));
		connect(action, SIGNAL(triggered()), m_editorController, SLOT(SaveImageHandler()));

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
	connect(m_clearScreenAction, SIGNAL(triggered()), m_editorController, SLOT(ClearImageHandler()));
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
	m_saveAsMenu = new QMenu(tr("&Save As"), this);
	for (auto& action : m_saveAsActions)
	{
		m_saveAsMenu->addAction(action);
	}

	m_fileMenu = new QMenu(tr("&File"), this);
	m_fileMenu->addAction(m_openFileAction);
	m_fileMenu->addMenu(m_saveAsMenu);
	m_fileMenu->addSeparator();
	m_fileMenu->addAction(m_exitAction);

	m_optionMenu = new QMenu(tr("&Options"), this);
	m_optionMenu->addAction(m_penColorChangeAction);
	m_optionMenu->addAction(m_penSizeChangeAction);
	m_optionMenu->addSeparator();
	m_optionMenu->addAction(m_clearScreenAction);

	m_helpMenu = new QMenu(tr("&Help"), this);
	m_helpMenu->addAction(m_openAboutAction);
	m_helpMenu->addAction(m_openAboutFrameworkAction);

	menuBar()->addMenu(m_fileMenu);
	menuBar()->addMenu(m_optionMenu);
	menuBar()->addMenu(m_helpMenu);
}

bool Paint::HasUnsavedChanges()
{
	if (!m_document->HasUnsavedChanges())
	{
		return false;
	}

	QMessageBox::StandardButton ret;

	ret = QMessageBox::warning(this, tr("Paint"),
		tr("The image has been modified.\n"
		   "Do you want to save your changes?"),
		QMessageBox::Save | QMessageBox::Discard
			| QMessageBox::Cancel);

	if (ret == QMessageBox::Save)
	{
		SaveFile(DEFAULT_SAVE_FORMAT);

		return false;
	}

	return true;
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

	auto image = createQImageFromImage(m_document->GetImage());

	if (image.save(fileName, fileFormat))
	{
		return true;
	}
	
	return false;
}