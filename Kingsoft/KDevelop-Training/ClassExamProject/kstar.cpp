#include "kstar.h"
#include <QPainter>
#include <QtMath>

KStar::KStar(QObject* parent)
	: KShape(parent)
{
	m_drawFlag = KGlobalData::KDrawFlag::StarDrawFlag;//为了复制，得到这个，让工厂重新做一个
}

KStar::~KStar()
{
}

void KStar::setStartPoint(const QPoint& pos)
{
	m_startPoint = pos;
}

void KStar::setEndPoint(const QPoint& pos)
{
	m_endPoint = pos;
	m_boundingRect = QRect(m_startPoint * m_scale, m_endPoint * m_scale).normalized(); // 规范化, 让大点在下
	updateStarPoints();
}

void KStar::move(QPoint offset)
{
	m_boundingRect.translate(offset * m_scale); // 移动外接矩形
	m_startPoint += offset;
	m_endPoint += offset;
	updateStarPoints();
}

KShapeType KStar::getShapeType()
{
	return KShapeType::StarShapeType; // 需要在枚举类型中添加 StarShapeType
}

void KStar::drawShape(QPaintDevice* parent)
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
	QVector<QPoint> points = calculateStarPoints(m_boundingRect);
	painter.drawPolygon(points);
}

QVector<QPoint> KStar::calculateStarPoints(const QRect& boundingRect)
{
	QVector<QPoint> points;

	// 左边1
	points.append(QPoint(boundingRect.left(), boundingRect.top() + 2 * boundingRect.height() / 5));

	// 中间偏左
	points.append(QPoint(boundingRect.left() +  7 * boundingRect.width() / 18, boundingRect.top() - boundingRect.height() / 72 + 2 * boundingRect.height() / 5));

	// 上中
	points.append(QPoint(boundingRect.left() + boundingRect.width() / 2, boundingRect.top()));

	//中间偏右
	points.append(QPoint(boundingRect.left() + boundingRect.width() - 7 * boundingRect.width() / 18, boundingRect.top() - boundingRect.height() / 72 + 2 * boundingRect.height() / 5));

	// 右边1
	points.append(QPoint(boundingRect.left() + boundingRect.width(), boundingRect.top() + 2 * boundingRect.height() / 5));

	//45/360   右边偏下
	points.append(QPoint(boundingRect.right() - 110 * boundingRect.width() / 360 , boundingRect.top() + boundingRect.height() / 2 + 45 * boundingRect.height() / 360));

	//下右
	points.append(QPoint(boundingRect.right() - 100 * boundingRect.width() / 505, boundingRect.bottom()));

	//下中间
	points.append(QPoint(boundingRect.left() + boundingRect.width() / 2, boundingRect.bottom() - 112 * boundingRect.height() / 505));

	//下左
	points.append(QPoint(boundingRect.left() + 100 * boundingRect.width() / 505, boundingRect.bottom()));

	//中左偏下
	points.append(QPoint(boundingRect.left() + 110 * boundingRect.width() / 360, boundingRect.top() + boundingRect.height() / 2 + 45 * boundingRect.height() / 360));
	return points;
}

void KStar::updateBoundingRect()
{
	if (m_starPoints.isEmpty())
		return;

	int minX = m_starPoints[0].x();
	int minY = m_starPoints[0].y();
	int maxX = m_starPoints[0].x();
	int maxY = m_starPoints[0].y();

	for (const QPoint& point : m_starPoints)
	{
		if (point.x() < minX) minX = point.x();
		if (point.y() < minY) minY = point.y();
		if (point.x() > maxX) maxX = point.x();
		if (point.y() > maxY) maxY = point.y();
	}

	m_boundingRect = QRect(QPoint(minX, minY), QPoint(maxX, maxY));
}

void KStar::updateStarPoints()
{
	m_starPoints = calculateStarPoints(m_boundingRect);
}

void KStar::moveTopLeft(QPoint pos)
{
	m_boundingRect.setTopLeft(pos);
	updateStarPoints();
	KShape::moveTopLeft(pos);
}

void KStar::moveTop(QPoint pos)
{
	m_boundingRect.setTop(pos.y());
	updateStarPoints();
	KShape::moveTop(pos);
}

void KStar::moveTopRight(QPoint pos)
{
	m_boundingRect.setTopRight(pos);
	updateStarPoints();
	KShape::moveTopRight(pos);
}

void KStar::moveLeft(QPoint pos)
{
	m_boundingRect.setLeft(pos.x());
	updateStarPoints();
	KShape::moveLeft(pos);
}

void KStar::moveRight(QPoint pos)
{
	m_boundingRect.setRight(pos.x());
	updateStarPoints();
	KShape::moveRight(pos);
}

void KStar::moveBottomLeft(QPoint pos)
{
	m_boundingRect.setBottomLeft(pos);
	updateStarPoints();
	KShape::moveBottomLeft(pos);
}

void KStar::moveBottom(QPoint pos)
{
	m_boundingRect.setBottom(pos.y());
	updateStarPoints();
	KShape::moveBottom(pos);
}

void KStar::moveBottomRight(QPoint pos)
{
	m_boundingRect.setBottomRight(pos);
	updateStarPoints();
	KShape::moveBottomRight(pos);
}

void KStar::setSideWidth(double width)
{
	m_lineWidth = width;
}

void KStar::setFilColor(QString color)
{
	m_fillColor = QColor(color);
}

void KStar::setLineColor(QString lineColor)
{
	m_lineColor = QColor(lineColor);
}

void KStar::setLineStyle(Qt::PenStyle lineStyle)
{
	m_lineStyle = lineStyle;
}
void KStar::setScale(qreal scale)
{
	m_scale = scale;

	QPoint newStartPoint = m_startPoint * m_scale;
	QPoint newEndPoint = m_endPoint * m_scale;

	m_boundingRect = QRect(newStartPoint, newEndPoint).normalized();
	
}

void KStar::drawShape(QPainter* painter)
{
	painter->setRenderHint(QPainter::Antialiasing);
	QPen pen;
	pen.setColor(m_lineColor);
	pen.setWidthF(m_lineWidth);

	pen.setStyle(m_lineStyle);

	painter->setPen(pen);
	QBrush brush(m_fillColor);
	painter->setBrush(brush);
	QVector<QPoint> points = calculateStarPoints(m_boundingRect);
	painter->drawPolygon(points);
}

void KStar::setBoundingRect(QRect boundingRect)
{
	m_boundingRect = boundingRect;
}

QRect KStar::getBoundingRect()
{
	return m_boundingRect;
}

void KStar::setPoints(QVector<QPoint> starPoints)
{
	m_starPoints = starPoints;
}

QVector<QPoint> KStar::getPoints()
{
	return m_starPoints;
}

KGlobalData::KDrawFlag KStar::getDrawFlag()
{
	return m_drawFlag;
}

void KStar::setDrawFlag(KGlobalData::KDrawFlag drawFlag)
{
	m_drawFlag = drawFlag;
}
