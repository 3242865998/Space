#ifndef __K_STAR_H__
#define __K_STAR_H__

#include "kshape.h"

class KStar : public KShape
{
	Q_OBJECT

public:
	KStar(QObject* parent = Q_NULLPTR);
	~KStar();

	void setStartPoint(const QPoint& pos);

	// 设置五角星终点
	void setEndPoint(const QPoint& pos);

	void move(QPoint offset) override;

	// 获取图形类型
	virtual KShapeType getShapeType() override;
	virtual void drawShape(QPaintDevice* parent = Q_NULLPTR) override;

	void updateStarPoints(); // 更新位置

	// 外边框调整函数
	void moveTopLeft(QPoint pos) override;
	void moveTop(QPoint pos) override;
	void moveTopRight(QPoint pos) override;
	void moveLeft(QPoint pos) override;
	void moveRight(QPoint pos) override;
	void moveBottomLeft(QPoint pos) override;
	void moveBottom(QPoint pos) override;
	void moveBottomRight(QPoint pos) override;

	//设置线宽
	void setSideWidth(double width) override;
	void setFilColor(QString color) override;
	void setLineColor(QString lineColor) override;
	void setLineStyle(Qt::PenStyle lineStyle)override;
	void setScale(qreal scale) override;
	//为了保存多个图片
	void drawShape(QPainter* painter) override;

	//为了复制
	void setBoundingRect(QRect boundingRect);
	QRect getBoundingRect();
	void setPoints(QVector<QPoint> starPoints);
	QVector<QPoint> getPoints();

	KGlobalData::KDrawFlag getDrawFlag() override;
	void setDrawFlag(KGlobalData::KDrawFlag drawFlag) override;
private:
	QVector<QPoint> calculateStarPoints(const QRect& boundingRect);
	QRect m_boundingRect; // 五角星的外接矩形
	QVector<QPoint> m_starPoints; // 五角星顶点
	void updateBoundingRect(); // 更新外接矩形
};

#endif
