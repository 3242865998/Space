#ifndef __K_LINE_H__
#define __K_LINE_H__

#include "kshape.h"

class KLine : public KShape
{
	Q_OBJECT
public:
	KLine(QObject* parent = nullptr);
	~KLine();

	void setEndPoint(const QPoint& pos);
	KShapeType getShapeType() override;
	void drawShape(QPaintDevice* parent) override;
	void move(QPoint offset) override;

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
private:
	//画直线只需要两个点，shape中已经有了
};

#endif 
