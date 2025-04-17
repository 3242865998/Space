#include "kfive.h"
#include <QPainter>
#include <QtMath>

KFive::KFive(QObject* parent)
	: KShape(parent)
{
	m_drawFlag = KGlobalData::KDrawFlag::FiveDrawFlag;//为了复制，得到这个，让工厂重新做一个
}

KFive::~KFive()
{
}
void KFive::setStartPoint(const QPoint& pos)
{
	m_startPoint = pos;
}
void KFive::setEndPoint(const QPoint& pos)
{
	m_endPoint = pos;
	m_boundingRect = QRect(m_startPoint * m_scale, m_endPoint * m_scale).normalized(); // 规范化,让大点再下
	updateFivePoints();
}

void KFive::move(QPoint offset)
{
	m_boundingRect.translate(offset * m_scale); // 移动外接矩形
	m_startPoint += offset;
	m_endPoint += offset;
	updateFivePoints();
}

KShapeType KFive::getShapeType()
{
	return KShapeType::FiveShapeType;
}

void KFive::drawShape(QPaintDevice* parent)
{
	QPainter painter(parent);
	painter.setRenderHint(QPainter::Antialiasing);
	QPen pen;
	pen.setColor(m_lineColor);

	pen.setStyle(m_lineStyle);

	pen.setWidthF(m_lineWidth);

	painter.setPen(pen);

	QBrush brush(m_fillColor);
	painter.setBrush(brush);

	QVector<QPoint> points = calculateFivePoints(m_boundingRect);
	painter.drawPolygon(points);
}

void KFive::drawShape(QPainter* painter)
{
	painter->setRenderHint(QPainter::Antialiasing);
	QPen pen;
	pen.setColor(m_lineColor);
	pen.setWidthF(m_lineWidth);
	pen.setStyle(m_lineStyle);
	painter->setPen(pen);
	QBrush brush(m_fillColor);
	painter->setBrush(brush);
	QVector<QPoint> points = calculateFivePoints(m_boundingRect);
	painter->drawPolygon(points);
}

void KFive::setBoundingRect(QRect boundingRect)
{
	m_boundingRect = boundingRect;
}

QRect KFive::getBoundingRect()
{
	return m_boundingRect;
}

void KFive::setPoints(QVector<QPoint> fivePoints)
{
	m_fivePoints = fivePoints;
}

QVector<QPoint> KFive::getPoints()
{
	return m_fivePoints;
}

KGlobalData::KDrawFlag KFive::getDrawFlag()
{
	return m_drawFlag;
}

void KFive::setDrawFlag(KGlobalData::KDrawFlag drawFlag)
{
	m_drawFlag = drawFlag;
}

QVector<QPoint> KFive::calculateFivePoints(const QRect& boundingRect)
{
	QVector<QPoint> points;

	// 左边中间
	points.append(QPoint(boundingRect.left(), boundingRect.top() + 3 * boundingRect.height() / 8));

	// 上边中间
	points.append(QPoint(boundingRect.left() + boundingRect.width() / 2, boundingRect.top()));

	// 右边中间
	points.append(QPoint(boundingRect.right(), boundingRect.top() + 3 * boundingRect.height() / 8));
	
	// 下边右边四分之一处
	points.append(QPoint(boundingRect.left() + 3 * boundingRect.width() / 4, boundingRect.bottom()));
	
	// 下边左边四分之一处
	points.append(QPoint(boundingRect.left() + boundingRect.width() / 4, boundingRect.bottom()));



	return points;
}

void KFive::updateBoundingRect()
{
	if (m_fivePoints.isEmpty())
		return;
	int minX = m_fivePoints[0].x();
	int minY = m_fivePoints[0].y();
	int maxX = m_fivePoints[0].x();
	int maxY = m_fivePoints[0].y();

	for (const QPoint& point : m_fivePoints)
	{
		if (point.x() < minX) minX = point.x();
		if (point.y() < minY) minY = point.y();
		if (point.x() > maxX) maxX = point.x();
		if (point.y() > maxY) maxY = point.y();
	}

	m_boundingRect = QRect(QPoint(minX, minY), QPoint(maxX, maxY));
	
}

void KFive::updateFivePoints()
{
	m_fivePoints = calculateFivePoints(m_boundingRect);
	//updateBoundingRect();
}

void KFive::moveTopLeft(QPoint pos)
{
	m_boundingRect.setTopLeft(pos);
	updateFivePoints();
	KShape::moveTopLeft(pos);
}

void KFive::moveTop(QPoint pos)
{
	m_boundingRect.setTop(pos.y());
	updateFivePoints();
	KShape::moveTop(pos);
}

void KFive::moveTopRight(QPoint pos)
{
	m_boundingRect.setTopRight(pos);
	updateFivePoints();
	KShape::moveTopRight(pos);
}

void KFive::moveLeft(QPoint pos)
{
	m_boundingRect.setLeft(pos.x());
	updateFivePoints();
	KShape::moveLeft(pos);
}

void KFive::moveRight(QPoint pos)
{
	m_boundingRect.setRight(pos.x());
	updateFivePoints();
	KShape::moveRight(pos);
}

void KFive::moveBottomLeft(QPoint pos)
{
	m_boundingRect.setBottomLeft(pos);
	updateFivePoints();
	KShape::moveBottomLeft(pos);
}

void KFive::moveBottom(QPoint pos)
{
	m_boundingRect.setBottom(pos.y());
	updateFivePoints();
	KShape::moveBottom(pos);
}

void KFive::moveBottomRight(QPoint pos)
{
	m_boundingRect.setBottomRight(pos);
	updateFivePoints();
	KShape::moveBottomRight(pos);
}

void KFive::setSideWidth(double width)
{
	m_lineWidth = width;
}

void KFive::setFilColor(QString color)
{
	m_fillColor = QColor(color);
}

void KFive::setLineColor(QString lineColor)
{
	m_lineColor = QColor(lineColor);
}

void KFive::setLineStyle(Qt::PenStyle lineStyle)
{
	m_lineStyle = lineStyle;
}

void KFive::setScale(qreal scale)
{
	m_scale = scale;

	QPoint newStartPoint = m_startPoint * m_scale;
	QPoint newEndPoint = m_endPoint * m_scale;

	m_boundingRect = QRect(newStartPoint, newEndPoint).normalized();

}

