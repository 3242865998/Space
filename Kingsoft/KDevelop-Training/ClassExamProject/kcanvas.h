#ifndef __K_CANVAS_H_
#define __K_CANVAS_H_

#include <QWidget>
#include <QSvgRenderer>//这两个为了导入
#include <QFileDialog>

#include "kshape.h"
#include "kglobaldata.h"
#include "krightmenu.h"
#include <QVector>

enum class KTransType
{
	None = 0,
	TopLeft, 
	Top,
	TopRight,
	Left,
	Contains,// 全部 
	Right,
	BottomLeft,
	Bottom,
	BottomRight
};


class KCanvas : public QWidget
{
	Q_OBJECT

public:
	KCanvas(QWidget *parent = Q_NULLPTR);
	~KCanvas();

	void initConnet();
	void handleRedo();
	void handleUndo();
	void handleDelete();
	void handleMoveUp();
	void handleMoveToFront();
	void handleMoveToBack();
	void handleMoveDown();
	void handleCopy();
	void handlePaste();
	void handleOverwrite();
	void handleCut();


	virtual void paintEvent(QPaintEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;
	
	KShape* getCurrentShape(const QPoint &pos);;// 获取当前位置图形
	KTransType getTransType(const QPoint &pos); // 获取移动类型
	void updateCusorStyle(KGlobalData::KDrawFlag flag, KTransType transType);
	void dragMoveShape(KTransType transType,const QPoint &pos);

	KShape* setShapePersonality(KShape* shape, KShape* mainShape);//用来设置深拷贝属性的

	KShape* setShapePersonalityNoOffset(KShape* tempShape, KShape* mainShape);

	//person
	//void onScaleChanged(qreal scale);
	void onSideWidthChanged(double lineWidth);
	void onShapeColorChanged(QString shapeColor);
	void onLineColorChanged(QString lineColor);
	void onLineStyleHandle(int index);
	//用于自动图形缩放
	void onScaleShapeChanged(double scale);
	//void onShapeColorChanged(const QString& color);
	//void onSideColorChanged(const QString& color);
	QPoint changingWithScale(const QPoint& pos);

	void clearAllShape();//新建文件
	void saveToSvg();//保存图片
	void openSvg();
	void exportToPng();
	
	//打开svg
	//存入本地svg
	//person
	void saveState();  // 保存当前状态到历史记录,undo\redo

	void handleSelectAll();


	 void keyPressEvent(QKeyEvent* event) override;

	
private:
	KShape* m_pCurrentShape;
	QList <KShape*> m_pShapeList;// 存储当前画布中的图形
	QList<QList<KShape*>> m_shapeHistory;  // 用于undo
	QList<QList<KShape*>> m_redoStack;  // 用于redo
	
	QPoint m_lastPos;// 记录前一次的位置
	KTransType m_TransType;// 记录移动类型
	
	bool m_isLPress;// 标记鼠标左键
	bool m_isDrawing;// 是否绘图
	bool m_isSelected;// 是否为选中


	QSvgRenderer* m_svgRenderer; // 用来存储导入的svg文件

	KRightMenu* m_rightMenu;
	bool m_isShapeSelected;//判断右键的前置条件
	QVector<KShape*> m_pCopyShape;//临时存储复制的图像

	QList<KShape*> m_pSelectedShapes;//放置全选图形

	bool m_isAllSelected; // 标志位：是否全选
	bool m_pEverAllSelected = false;
};

#endif


