#ifndef __K_CIRCLE_H__
#define __K_CIRCLE_H__

#include "kshape.h"

class KCircle : public KShape
{
	Q_OBJECT

public:
	KCircle(QObject* parent = Q_NULLPTR);
	~KCircle();

	void setStartPoint(const QPoint& point);

	// 设置圆形终点
	void setEndPoint(const QPoint& pos);
	

	virtual void move(QPoint offset) override;

	// 获取图形类型
	virtual KShapeType getShapeType() override;
	virtual void drawShape(QPaintDevice* parent = Q_NULLPTR) override;

	// 外边框调整函数
	void moveTopLeft(QPoint pos) override;
	void moveTop(QPoint pos) override;
	void moveTopRight(QPoint pos) override;
	void moveLeft(QPoint pos) override;
	void moveRight(QPoint pos) override;
	void moveBottomLeft(QPoint pos) override;
	void moveBottom(QPoint pos) override;
	void moveBottomRight(QPoint pos) override;

	KGlobalData::KDrawFlag getDrawFlag() override;
	void setDrawFlag(KGlobalData::KDrawFlag drawFlag) override;


	//设置线宽
	void setSideWidth(double width) override;
	//填充颜色
	void setFilColor(QString color) override;
	//边框颜色
	void setLineColor(QString lineColor) override;
	//边框样式
	void setLineStyle(Qt::PenStyle lineStyle) override;
	//缩放
	void setScale(qreal scale) override;
	//为了保存多个图片
	void drawShape(QPainter* painter) override;
	
	
	
private:
	QRect m_boundingRect; // 椭圆的外接矩形
};

#endif 
