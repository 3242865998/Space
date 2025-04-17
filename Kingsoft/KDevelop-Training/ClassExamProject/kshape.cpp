#include "kshape.h"
#include <qDebug>
KShape::KShape(QObject *parent)
	: QObject(parent)
{
}

KShape::~KShape()
{
}

void KShape::move(QPoint offset)
{
	m_startPoint += offset;
	m_endPoint += offset;
}

void KShape::moveTop(QPoint pos)
{
	m_startPoint.ry() = pos.y();
}

void KShape::moveBottom(QPoint pos)
{
	m_endPoint.ry() = pos.y();
}

void KShape::moveLeft(QPoint pos)
{
	m_startPoint.rx() = pos.x();
}

void KShape::moveRight(QPoint pos)
{
	m_endPoint.rx() = pos.x();
}

void KShape::moveTopLeft(QPoint pos)
{
	m_startPoint = pos;
}

void KShape::moveTopRight(QPoint pos)
{
	m_startPoint.ry() = pos.y();
	m_endPoint.rx() = pos.x();
}

void KShape::moveBottomLeft(QPoint pos)
{
	m_startPoint.rx() = pos.x();
	m_endPoint.ry() = pos.y();
}

void KShape::moveBottomRight(QPoint pos)
{
	m_endPoint = pos;
}

// 绘制选中矩形框
//任何图形都是基于矩形来绘制的
void KShape::drawOutLine(QPaintDevice* parent)
{
	QPainter painter(parent);
	QPen pen;

	pen.setColor(QColor(79, 128, 255));
	pen.setWidth(3);
	painter.setPen(pen);

	QPoint start = getStartPoint() ;
	QPoint end = getEndPoint();

	//painter.drawRect(QRect(getStartPoint(), getEndPoint()));
	painter.drawRect(QRect(getStartPoint() * m_scale, getEndPoint() * m_scale));
}

QPoint KShape::getStartPoint()
{
	return m_startPoint;
}

QPoint KShape::getEndPoint()
{
	return m_endPoint;
}

void KShape::setStartPoint(const QPoint & point)
{
	
	m_startPoint = point;
}

void KShape::setEndPoint(const QPoint& point)
{
	
	m_endPoint = point;
}

KShapeType KShape::getShapeType()
{
	return KShapeType();
}

QRect KShape::getShapeRect() const
{
	

	return QRect(m_startPoint ,m_endPoint );
}


bool KShape::isValid()
{
	return (m_startPoint.x() != m_endPoint.x() || m_startPoint.y() != m_endPoint.y());
}

void KShape::setSideWidth(double width)
{
	m_lineWidth = width;
}

double KShape::getSideWidth()
{
	return m_lineWidth;
}

void KShape::setFilColor(QString color)
{
	m_fillColor = color;
}

QString KShape::getFilColor()
{
	//qInfo() << m_fillColor.name(QColor::HexArgb);
	return m_fillColor.name(QColor::HexArgb);
}

void KShape::setLineColor(QString lineColor)
{
	m_lineColor = QColor(lineColor);
}

QString KShape::getLineColor()
{
	return m_lineColor.name();
}

void KShape::setLineStyle(Qt::PenStyle lineStyle)
{
	m_lineStyle = lineStyle;
}

Qt::PenStyle KShape::getLineStyle()
{
	return m_lineStyle;
}

void KShape::setScale(qreal scale)
{
	m_scale = scale;
}

qreal KShape::getScale()
{
	return m_scale;
}

KGlobalData::KDrawFlag KShape::getDrawFlag()
{

	return m_drawFlag;
}

void KShape::setDrawFlag(KGlobalData::KDrawFlag drawFlag)
{
	m_drawFlag = drawFlag;
}

void KShape::setBoundingRect(QRect boundingRect)
{
}

QRect KShape::getBoundingRect()
{
	return QRect();
}

void KShape::setPoints(QVector<QPoint> starPoints)
{
}

QVector<QPoint> KShape::getPoints()
{
	return QVector<QPoint>();
}

