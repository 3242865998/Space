#include "kline.h"

KLine::KLine(QObject* parent)
	:KShape(parent)
{
	m_drawFlag = KGlobalData::KDrawFlag::LineDrawFlag;//为了复制，得到这个，让工厂重新做一个
}

KLine::~KLine()
{
}

void KLine::setEndPoint(const QPoint& pos)
{

	m_endPoint = pos;
}

KShapeType KLine::getShapeType()
{
	return KShapeType::LineShapeType;
}

void KLine::drawShape(QPaintDevice* parent)
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

	//painter.drawLine(m_startPoint, m_endPoint);
	//scale
	painter.drawLine(m_startPoint * m_scale, m_endPoint * m_scale);
}

void KLine::move(QPoint offset)
{
	m_startPoint += offset;
	m_endPoint += offset;
}

void KLine::setSideWidth(double width)
{
	m_lineWidth = width;
}

void KLine::setFilColor(QString color)
{
	m_fillColor = QColor(color);
}

void KLine::setLineColor(QString lineColor)
{
	m_lineColor = QColor(lineColor);
}

void KLine::setLineStyle(Qt::PenStyle lineStyle)
{
	m_lineStyle = lineStyle;
}

void KLine::setScale(qreal scale)
{
	m_scale = scale;
}

void KLine::drawShape(QPainter* painter)
{
	
	painter->setRenderHint(QPainter::Antialiasing);
	QPen pen;
	pen.setColor(m_lineColor);
	pen.setWidthF(m_lineWidth);

	pen.setStyle(m_lineStyle);

	painter->setPen(pen);

	QBrush brush(m_fillColor);
	painter->setBrush(brush);

	//painter.drawLine(m_startPoint, m_endPoint);
	//scale
	painter->drawLine(m_startPoint * m_scale, m_endPoint * m_scale);
}

KGlobalData::KDrawFlag KLine::getDrawFlag()
{
	return m_drawFlag;
}

void KLine::setDrawFlag(KGlobalData::KDrawFlag drawFlag)
{
	m_drawFlag = drawFlag;
}

