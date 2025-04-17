#ifndef __K_SHAPE_H_
#define __K_SHAPE_H_

#include <QObject>
#include <QPoint>
#include <QPaintDevice>
#include <QPainter>
#include "kglobaldata.h"
enum class KShapeType
{
	None = 0,
	PenShapeType,
	LineShapeType,
	CircleShapeType,
	RectShapeType,
	FiveShapeType,
	SixShapeType,
	TextShapeType,
	StarShapeType
};

class KShape : public QObject
{
	Q_OBJECT

public:
	
	KShape(QObject *parent = Q_NULLPTR);
	~KShape();
	
	// 在子类中重写，实现不同类型的图形的绘制
	virtual void drawShape(QPaintDevice *parent = Q_NULLPTR) = 0;
	

	virtual void move(QPoint offset);
	virtual void moveTop(QPoint pos);
	virtual void moveBottom(QPoint pos);
	virtual void moveLeft(QPoint pos);
	virtual void moveRight(QPoint pos);
	virtual void moveTopLeft(QPoint pos);
	virtual void moveTopRight(QPoint pos);
	virtual void moveBottomLeft(QPoint pos);
	virtual void moveBottomRight(QPoint pos);
	virtual KShapeType getShapeType();
	

	QPoint getStartPoint();
	QPoint getEndPoint();

	void setStartPoint(const QPoint &point);
	void setEndPoint(const QPoint &point);
	

	void drawOutLine(QPaintDevice* parent = Q_NULLPTR);
	QRect getShapeRect() const;
	bool isValid();

	virtual void setSideWidth(double width);
	double getSideWidth();
	virtual void setFilColor(QString color);
	QString getFilColor();
	virtual void setLineColor(QString lineColor);
	QString getLineColor();

	virtual void setLineStyle(Qt::PenStyle lineStyle);
	Qt::PenStyle getLineStyle();
	virtual void setScale(qreal scale);
	qreal getScale();
	virtual void drawShape(QPainter* painter) = 0; // 确保drawShape接收QPainter*,为了保存多个图形
	
	virtual KGlobalData::KDrawFlag getDrawFlag();
	virtual void setDrawFlag(KGlobalData::KDrawFlag drawFlag);

	//为了复制,主要为了star、five、six、pen
	void setBoundingRect(QRect boundingRect);
	QRect getBoundingRect();
	virtual void setPoints(QVector<QPoint> starPoints);
	virtual QVector<QPoint> getPoints();


protected:
	QPoint m_startPoint;// 起始坐标
	QPoint m_endPoint; // 结束坐标
	double m_lineWidth = 1.5;
	QColor m_fillColor = "#00000000"; // 填充颜色成员变量
	QColor m_lineColor = "#000000"; // 边框颜色，也就是线
	Qt::PenStyle m_lineStyle = Qt::SolidLine;
	qreal m_scale = KGlobalData::getGlobalDataIntance()->getCanvasScale();

	//放缩需要
	QPoint m_lastStartPoint;// 起始坐标
	QPoint m_lastEndPoint; // 结束坐标

	KGlobalData::KDrawFlag m_drawFlag = KGlobalData::KDrawFlag::NoneDrawFlag;
};

#endif
