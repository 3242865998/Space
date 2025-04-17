#include "kfilemenu.h"
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include "kmainwindow.h"

KFileMenu::KFileMenu(KMainWindow* mainWindow, QWidget* parent)
	: QMenuBar(parent)
	, m_mainWindow(mainWindow)
{
	// 创建“文件”菜单
	QMenu* fileMenu = new QMenu(QString::fromLocal8Bit("文件"), this);

	// 创建菜单项
	QAction* newFileAction = new QAction(QString::fromLocal8Bit("新建文件"), this);
	newFileAction->setShortcut(QKeySequence("Ctrl+N"));
	connect(newFileAction, &QAction::triggered, m_mainWindow, &KMainWindow::newFile);

	QAction* openSVGAction = new QAction(QString::fromLocal8Bit("打开SVG"), this);
	openSVGAction->setShortcut(QKeySequence("Ctrl+O"));
	connect(openSVGAction, &QAction::triggered, m_mainWindow, &KMainWindow::openSVG);

	QAction* saveAction = new QAction(QString::fromLocal8Bit("保存"), this);
	saveAction->setShortcut(QKeySequence("Ctrl+S"));
	connect(saveAction, &QAction::triggered, m_mainWindow, &KMainWindow::saveSvgToLocal);

	QAction* exportPNGAction = new QAction(QString::fromLocal8Bit("导出PNG"), this);
	exportPNGAction->setShortcut(QKeySequence("Ctrl+E"));
	connect(exportPNGAction, &QAction::triggered, m_mainWindow, &KMainWindow::exportPNG);

	// 将菜单项添加到“文件”菜单中
	fileMenu->addAction(newFileAction);
	fileMenu->addAction(openSVGAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(exportPNGAction);

	// 将“文件”菜单添加到菜单栏
	this->addMenu(fileMenu);
}

void KFileMenu::newFile()
{
	QMessageBox::information(m_mainWindow, QString::fromLocal8Bit("新建文件"), QString::fromLocal8Bit("新建文件功能被调用"));
}

void KFileMenu::openSVG()
{
	QMessageBox::information(m_mainWindow, QString::fromLocal8Bit("打开SVG"), QString::fromLocal8Bit("打开SVG功能被调用"));
}

void KFileMenu::save()
{
	QMessageBox::information(m_mainWindow, QString::fromLocal8Bit("保存"), QString::fromLocal8Bit("保存功能被调用"));
}

void KFileMenu::exportPNG()
{
	QMessageBox::information(m_mainWindow, QString::fromLocal8Bit("导出PNG"), QString::fromLocal8Bit("导出PNG功能被调用"));
}
