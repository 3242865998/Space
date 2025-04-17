#ifndef __K_PEN_H__
#define __K_PEN_H__

#include "kshape.h"
class KPen : public KShape
{
	Q_OBJECT

public:
	KPen(QObject* parent = Q_NULLPTR);
	~KPen();

	void addPos(const QPoint& pos);

	//这个应该是用来移动线的，每个点都加一个偏移量
	virtual void move(QPoint offset) override;

	void setStartPoint();
	void setEndPoint();
	//
	virtual KShapeType getShapeType() override;
	virtual void drawShape(QPaintDevice* parent = Q_NULLPTR) override;

	//没有要求拖拉变形

	//设置线宽
	void setSideWidth(double width) override;
	void setFilColor(QString color) override;
	void setLineColor(QString lineColor) override;
	void setLineStyle(Qt::PenStyle lineStyle) override;

	void setScale(qreal scale) override;
	//为了保存多个图片
	void drawShape(QPainter* painter) override;

	void setPoints(QVector<QPoint> posVector) override;
	QVector<QPoint> getPoints() override;

	KGlobalData::KDrawFlag getDrawFlag() override;
	void setDrawFlag(KGlobalData::KDrawFlag drawFlag) override;
private:
	QVector<QPoint> m_posVector;
	
	
	
};

#endif


