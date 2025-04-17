#include "ksvgmainwindow.h"
#include <QApplication>
#include <QWheelEvent>
#include <qDebug>
KSvgMainWindow::KSvgMainWindow(QWidget *parent)
	: QScrollArea(parent)
	, m_pCanvas(Q_NULLPTR)
{
	setFrameShape(QFrame::NoFrame); // 设置无边框

	// 当内容超过显示区域时出现滚动条
	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setStyleSheet("QScrollArea{background-color:#3f3f3c;}");
	setAlignment(Qt::AlignCenter);
	
	m_pCanvas = new KCanvas;
	setWidget(m_pCanvas);// 设置当前控件为滚动区域的子控件
}

void KSvgMainWindow::sideWidthHandle(double lineWidth)
{
		m_pCanvas->onSideWidthChanged(lineWidth);
}

void KSvgMainWindow::shapeColorHandle(QString shapeColor)
{
	m_pCanvas->onShapeColorChanged(shapeColor);
}
void KSvgMainWindow::lineColorHandle(QString lineColor)
{
	m_pCanvas->onLineColorChanged(lineColor);
}

void KSvgMainWindow::lineStyleHandle(int index)
{
	m_pCanvas->onLineStyleHandle(index);
}
void KSvgMainWindow::changedSizeSScaleCanvas(double scale)
{
	qint32 width = KGlobalData::getGlobalDataIntance()->getCanvasWidth();
	qint32 height = KGlobalData::getGlobalDataIntance()->getCanvasHeight();
	m_pCanvas->resize(width * scale, height * scale);
}
void KSvgMainWindow::scaleShapeHandle()
{
	m_pCanvas->onScaleShapeChanged(KGlobalData::getGlobalDataIntance()->getCanvasScale());
}
KSvgMainWindow::~KSvgMainWindow()
{
}

void KSvgMainWindow::setCustorStyle(KGlobalData::KDrawFlag drawFlag)
{
	switch (drawFlag)
	{
	case KGlobalData::KDrawFlag::PenDrawFlag:
		setCursor(Qt::ArrowCursor);
		break;
	case KGlobalData::KDrawFlag::LineDrawFlag:
	case KGlobalData::KDrawFlag::RectDrawFlag:
	case KGlobalData::KDrawFlag::CircleDrawFlag:
	case KGlobalData::KDrawFlag::FiveDrawFlag:
	case KGlobalData::KDrawFlag::SixDrawFlag:
	case KGlobalData::KDrawFlag::StarDrawFlag:
		setCursor(Qt::CrossCursor);
		break;

	case KGlobalData::KDrawFlag::TextDrawFlag:
		setCursor(Qt::IBeamCursor);
		break;
	default:
		setCursor(Qt::ArrowCursor);
		break;
	}
}

void KSvgMainWindow::enterEvent(QEvent* event)
{
	KGlobalData::KDrawFlag flag = KGlobalData::getGlobalDataIntance()->getDrawFlag();
	setCustorStyle(flag);
	//调用父对象方法进行处理
	QScrollArea::enterEvent(event);
}

//这里只是ctrl+wheel改变画布大小
void KSvgMainWindow::wheelEvent(QWheelEvent* event)
{
	if (QApplication::keyboardModifiers() == Qt::ControlModifier)
	{

		qDebug() << KGlobalData::getGlobalDataIntance()->getCanvasScale();
		qDebug() << event->delta();

		qreal scale = 1.0;
		if (event->delta() > 0)
			scale = KGlobalData::getGlobalDataIntance()->getCanvasScale() + 0.05;
		else
			scale = KGlobalData::getGlobalDataIntance()->getCanvasScale() - 0.05;

		qint32 width = KGlobalData::getGlobalDataIntance()->getCanvasWidth();
		qint32 height = KGlobalData::getGlobalDataIntance()->getCanvasHeight();
		m_pCanvas->resize(width * scale, height * scale);
		
		//这里没有跟着改变数值的大小,需要变动
		KGlobalData::getGlobalDataIntance()->setCanvaScale(scale);
		emit scaleChanged();
		emit canvasChanged();
	}

}

void KSvgMainWindow::newFile()
{
	m_pCanvas->clearAllShape();
}

void KSvgMainWindow::saveFile()
{
	m_pCanvas->saveToSvg();
}

void KSvgMainWindow::openLocalSvg()
{
	m_pCanvas->openSvg();
}

void KSvgMainWindow::exportSvgToPNG()
{
	m_pCanvas->exportToPng();
}
