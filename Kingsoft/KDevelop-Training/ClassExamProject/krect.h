#ifndef __K_RECT_H_
#define __K_RECT_H_

#include "kshape.h"

class KRect : public KShape
{
	Q_OBJECT

public:
	KRect(QObject *parent = Q_NULLPTR);
	~KRect();
	virtual void drawShape(QPaintDevice* parent = Q_NULLPTR) override;
	virtual KShapeType getShapeType();

	//设置线宽
	void setSideWidth(double width) override;
	void setFilColor(QString color) override;
	void setLineColor(QString lineColor) override;
	void setLineStyle(Qt::PenStyle lineStyle) override;

	void setScale(qreal scale) override;
	//为了保存多个图片
	void drawShape(QPainter* painter) override;

	KGlobalData::KDrawFlag getDrawFlag() override;
	void setDrawFlag(KGlobalData::KDrawFlag drawFlag) override;
};

#endif
