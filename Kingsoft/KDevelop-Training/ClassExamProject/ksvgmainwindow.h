#ifndef __K_SVG_MAINWINDOW_H_
#define __K_SVG_MAINWINDOW_H_

#include <QScrollArea>
#include "kcanvas.h"

class KSvgMainWindow : public QScrollArea
{
	Q_OBJECT
	friend class KMainWindow;

public:
	KSvgMainWindow(QWidget *parent);

	//person
	void sideWidthHandle(double lineWidth);
	void shapeColorHandle(QString shapeColor);
	void lineColorHandle(QString lineColor);
	void lineStyleHandle(int index);
	//用于手动设置scale
	void changedSizeSScaleCanvas(double scale);
	//哟关于图形跟着画布缩放
	void scaleShapeHandle();
	~KSvgMainWindow();
	void setCustorStyle(KGlobalData::KDrawFlag drawFlag);

	void enterEvent(QEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
	 
	void newFile();
	void saveFile();
	void openLocalSvg();
	void exportSvgToPNG();
signals:
	void canvasChanged();
signals:
	void scaleChanged();


private:
	KCanvas *m_pCanvas;
};

#endif
