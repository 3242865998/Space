#include "krightmenu.h"
#include <qDebug>

KRightMenu::KRightMenu(bool isShapeSelected, QWidget* parent) 
	: QMenu(parent) 
{
	if (isShapeSelected)
	{
		// 添加动作并设置快捷键
		addAction(QString::fromLocal8Bit("全选        Ctrl + A"), this, SLOT(selectAll()));
		addAction(QString::fromLocal8Bit("撤销(undo)  Ctrl + Z"), this, SLOT(undo()));
		addAction(QString::fromLocal8Bit("重做(redo)  Ctrl + Y"), this, SLOT(redo()));
		addAction(QString::fromLocal8Bit("剪切        Ctrl + X"), this, SLOT(cut()));
		addAction(QString::fromLocal8Bit("复制        Ctrl + C"), this, SLOT(copy()));
		addAction(QString::fromLocal8Bit("粘贴        Ctrl + V"), this, SLOT(paste()));
		addAction(QString::fromLocal8Bit("复写        Ctrl + D"), this, SLOT(overwrite()));
		addAction(QString::fromLocal8Bit("删除        Backspace"), this, SLOT(deleteItem()));
		addAction(QString::fromLocal8Bit("置上一层    Up"), this, SLOT(moveUp()));
		addAction(QString::fromLocal8Bit("置下一层    Down"), this, SLOT(moveDown()));
		addAction(QString::fromLocal8Bit("置最前      Left"), this, SLOT(moveToFront()));
		addAction(QString::fromLocal8Bit("置最后      Right"), this, SLOT(moveToBack()));

	}
	else
	{
		// 添加动作并设置快捷键
		addAction(QString::fromLocal8Bit("全选        Ctrl + A"), this, SLOT(selectAll()));
		addAction(QString::fromLocal8Bit("撤销(undo)  Ctrl + Z"), this, SLOT(undo()));
		addAction(QString::fromLocal8Bit("重做(redo)  Ctrl + Y"), this, SLOT(redo()));
		addAction(QString::fromLocal8Bit("粘贴        Ctrl + V"), this, SLOT(paste()));
		addAction(QString::fromLocal8Bit("复写        Ctrl + D"), this, SLOT(overwrite()));
		
	}
		

	
}

void KRightMenu::selectAll() 
{
	emit toCanvasHandleSelectAll();
}

void KRightMenu::undo() 
{
	emit toCanvasHandleUndo();
}

void KRightMenu::redo() 
{
	emit toCanvasHandleRedo();
}

void KRightMenu::cut()
{
	emit toCanvasHandleCut();
}

void KRightMenu::copy()
{
	emit toCanvasHandleCopy();
}

void KRightMenu::paste()
{
	emit toCanvasHandlePaste();
}

void KRightMenu::overwrite()
{
	emit toCanvasHandleOverwrite();
}

void KRightMenu::deleteItem()
{
	emit toCanvasHandleDelete();
}

void KRightMenu::moveUp()
{
	emit toCanvasHandleMoverUp();
}

void KRightMenu::moveDown()
{
	emit toCanvasHandleMoveDown();
}

void KRightMenu::moveToFront()
{
	emit toCanvasHandleMoveToFront();
}

void KRightMenu::moveToBack()
{
	emit toCanvasHandleMoveToBack();
}
