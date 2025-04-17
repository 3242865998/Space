#ifndef __K_RIGHT_MENU_H__
#define __K_RIGHT_MENU_H__

#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QKeySequence>
#include <QObject>
class KRightMenu : public QMenu
{
	Q_OBJECT
public:
	explicit KRightMenu(bool isShapeSelected = false, QWidget* parent = nullptr);
signals:
	void toCanvasHandleCut();
	void toCanvasHandleDelete();
	void toCanvasHandleCopy();
	void toCanvasHandlePaste();
	void toCanvasHandleOverwrite();
	void toCanvasHandleMoverUp();
	void toCanvasHandleMoveDown();
	void toCanvasHandleMoveToFront();
	void toCanvasHandleMoveToBack();
	void toCanvasHandleUndo();
	void  toCanvasHandleRedo();
	void toCanvasHandleSelectAll();

private slots:
	void selectAll();
	void undo();
	void redo();
	void cut();
	void copy();
	void paste();
	void overwrite();
	void deleteItem();
	void moveUp();
	void moveDown();
	void moveToFront();
	void moveToBack();
};

#endif
