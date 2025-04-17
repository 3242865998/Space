#include "krect.h"
#include <QPainter>

KRect::KRect(QObject *parent)
	: KShape(parent)
{
	m_drawFlag = KGlobalData::KDrawFlag::RectDrawFlag;//为了复制，得到这个，让工厂重新做一个
}

KRect::~KRect()
{
}

void KRect::drawShape(QPaintDevice* parent)
{
	QPainter painter(parent); 
	QPen pen;
	pen.setColor(m_lineColor);
	pen.setWidthF(m_lineWidth);

	pen.setStyle(m_lineStyle);

	painter.setPen(pen);
	QBrush brush(m_fillColor);
	painter.setBrush(brush);
	painter.drawRect(QRect(getStartPoint() * m_scale, getEndPoint() * m_scale)); 
}

KShapeType KRect::getShapeType()
{
	return KShapeType::RectShapeType;
}

void KRect::setSideWidth(double width)
{
	m_lineWidth = width;
}

void KRect::setFilColor(QString color)
{
	m_fillColor = QColor(color);
}

void KRect::setLineColor(QString lineColor)
{
	m_lineColor = QColor(lineColor);
}

void KRect::setLineStyle(Qt::PenStyle lineStyle)
{
	m_lineStyle = lineStyle;
}

void KRect::setScale(qreal scale)
{
	m_scale = scale;
}

void KRect::drawShape(QPainter* painter)
{
	QPen pen;
	pen.setColor(m_lineColor);
	pen.setWidthF(m_lineWidth);

	pen.setStyle(m_lineStyle);

	painter->setPen(pen);
	QBrush brush(m_fillColor);
	painter->setBrush(brush);
	painter->drawRect(QRect(getStartPoint() * m_scale, getEndPoint() * m_scale));
}

KGlobalData::KDrawFlag KRect::getDrawFlag()
{
	return m_drawFlag;
}

void KRect::setDrawFlag(KGlobalData::KDrawFlag drawFlag)
{
	m_drawFlag = drawFlag;
}


