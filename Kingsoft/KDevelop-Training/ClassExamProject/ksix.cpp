#include "ksix.h"
#include <QPainter>
#include <QtMath>

KSix::KSix(QObject* parent)
	: KShape(parent)
{
	m_drawFlag = KGlobalData::KDrawFlag::SixDrawFlag;//为了复制，得到这个，让工厂重新做一个
}

KSix::~KSix()
{
}
void KSix::setStartPoint(const QPoint& pos)
{
	m_startPoint = pos;
}
void KSix::setEndPoint(const QPoint& pos)
{
	m_endPoint = pos;
	m_boundingRect = QRect(m_startPoint * m_scale, m_endPoint * m_scale).normalized(); // 规范化,让大点再下
	updateFivePoints();
}

void KSix::move(QPoint offset)
{
	m_boundingRect.translate(offset * m_scale); // 移动外接矩形
	m_startPoint += offset;
	m_endPoint += offset;
	updateFivePoints();
}

KShapeType KSix::getShapeType()
{
	return KShapeType::FiveShapeType;
}

void KSix::drawShape(QPaintDevice* parent)
{
	QPainter painter(parent);
	painter.setRenderHint(QPainter::Antialiasing);
	QPen pen;
	pen.setColor(m_lineColor);
	pen.setWidthF(m_lineWidth);

	pen.setStyle(m_lineStyle);

	painter.setPen(pen);

	QBrush brush(m_fillColor);
	painter.setBrush(brush);
	
	QVector<QPoint> points = calculateSixPoints(m_boundingRect);
	painter.drawPolygon(points);
}

QVector<QPoint> KSix::calculateSixPoints(const QRect& boundingRect)
{
	QVector<QPoint> points;

	// 左边1
	points.append(QPoint(boundingRect.left(), boundingRect.top() +  boundingRect.height() / 4));

	// 上边中间
	points.append(QPoint(boundingRect.left() + boundingRect.width() / 2, boundingRect.top()));

	// 右边1
	points.append(QPoint(boundingRect.right(), boundingRect.top() +  boundingRect.height() / 4));

	// 右边2
	points.append(QPoint(boundingRect.right(), boundingRect.top() + 3 * boundingRect.height() / 4));

	// 下边中间
	points.append(QPoint(boundingRect.left() + boundingRect.width() / 2, boundingRect.bottom()));

	// 左边2
	points.append(QPoint(boundingRect.left(), boundingRect.top() + 3 * boundingRect.height() / 4));


	return points;
}

void KSix::updateBoundingRect()
{
	if (m_sixPoints.isEmpty())
		return;
	int minX = m_sixPoints[0].x();
	int minY = m_sixPoints[0].y();
	int maxX = m_sixPoints[0].x();
	int maxY = m_sixPoints[0].y();

	for (const QPoint& point : m_sixPoints)
	{
		if (point.x() < minX) minX = point.x();
		if (point.y() < minY) minY = point.y();
		if (point.x() > maxX) maxX = point.x();
		if (point.y() > maxY) maxY = point.y();
	}

	m_boundingRect = QRect(QPoint(minX, minY), QPoint(maxX, maxY));

}

void KSix::updateFivePoints()
{
	m_sixPoints = calculateSixPoints(m_boundingRect);
	//updateBoundingRect();
}

void KSix::moveTopLeft(QPoint pos)
{
	m_boundingRect.setTopLeft(pos);
	updateFivePoints();
	KShape::moveTopLeft(pos);
}

void KSix::moveTop(QPoint pos)
{
	m_boundingRect.setTop(pos.y());
	updateFivePoints();
	KShape::moveTop(pos);
}

void KSix::moveTopRight(QPoint pos)
{
	m_boundingRect.setTopRight(pos);
	updateFivePoints();
	KShape::moveTopRight(pos);
}

void KSix::moveLeft(QPoint pos)
{
	m_boundingRect.setLeft(pos.x());
	updateFivePoints();
	KShape::moveLeft(pos);
}

void KSix::moveRight(QPoint pos)
{
	m_boundingRect.setRight(pos.x());
	updateFivePoints();
	KShape::moveRight(pos);
}

void KSix::moveBottomLeft(QPoint pos)
{
	m_boundingRect.setBottomLeft(pos);
	updateFivePoints();
	KShape::moveBottomLeft(pos);
}

void KSix::moveBottom(QPoint pos)
{
	m_boundingRect.setBottom(pos.y());
	updateFivePoints();
	KShape::moveBottom(pos);
}

void KSix::moveBottomRight(QPoint pos)
{
	m_boundingRect.setBottomRight(pos);
	updateFivePoints();
	KShape::moveBottomRight(pos);
}

void KSix::setSideWidth(double width)
{
	m_lineWidth = width;
}

void KSix::setFilColor(QString color)
{
	m_fillColor = QColor(color);
}

void KSix::setLineColor(QString lineColor)
{
	m_lineColor = QColor(lineColor);
}

void KSix::setLineStyle(Qt::PenStyle lineStyle)
{
	m_lineStyle = lineStyle;
}

void KSix::setScale(qreal scale)
{
	m_scale = scale;

	QPoint newStartPoint = m_startPoint * m_scale;
	QPoint newEndPoint = m_endPoint * m_scale;

	m_boundingRect = QRect(newStartPoint, newEndPoint).normalized();
}

void KSix::drawShape(QPainter* painter)
{
	painter->setRenderHint(QPainter::Antialiasing);
	QPen pen;
	pen.setColor(m_lineColor);
	pen.setWidthF(m_lineWidth);

	pen.setStyle(m_lineStyle);

	painter->setPen(pen);

	QBrush brush(m_fillColor);
	painter->setBrush(brush);

	QVector<QPoint> points = calculateSixPoints(m_boundingRect);
	painter->drawPolygon(points);
}

void KSix::setBoundingRect(QRect boundingRect)
{
	m_boundingRect = boundingRect;
}

QRect KSix::getBoundingRect()
{
	return m_boundingRect;
}

void KSix::setPoints(QVector<QPoint> sixPoints)
{
	m_sixPoints = sixPoints;
}

QVector<QPoint> KSix::getPoints()
{
	return m_sixPoints;
}

KGlobalData::KDrawFlag KSix::getDrawFlag()
{
	return m_drawFlag;
}

void KSix::setDrawFlag(KGlobalData::KDrawFlag drawFlag)
{
	m_drawFlag = drawFlag;
}
