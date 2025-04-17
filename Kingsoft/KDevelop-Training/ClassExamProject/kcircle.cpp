#include "kcircle.h"
#include <QPainter>
#include <QtMath>
#include <qDebug>
#include "kglobaldata.h"
#include <QWidget>
KCircle::KCircle(QObject* parent)
	: KShape(parent)
{
	m_drawFlag = KGlobalData::KDrawFlag::CircleDrawFlag;//为了复制，得到这个，让工厂重新做一个
}

KCircle::~KCircle()
{
}
void KCircle::setStartPoint(const QPoint& point)
{
	m_startPoint = point;
}
void KCircle::setEndPoint(const QPoint& pos)
{
	m_endPoint = pos;
	m_boundingRect = QRect(m_startPoint * m_scale, m_endPoint * m_scale).normalized();//这里会返回规范化的矩形，用两个点来做矩形

	
}
//这是用来移动外接矩形的，可以保证移动椭圆
void KCircle::move(QPoint offset)
{
	m_boundingRect.translate(offset * m_scale); // 移动外接矩形
	m_startPoint += offset;
	m_endPoint += offset;

}
KShapeType KCircle::getShapeType()
{
	return KShapeType::CircleShapeType;
}

void KCircle::drawShape(QPaintDevice* parent)
{
	QPainter painter(parent);
	painter.setRenderHint(QPainter::Antialiasing);
	QPen pen;

	pen.setColor(m_lineColor);
	pen.setWidthF(m_lineWidth);

	//线形
	pen.setStyle(m_lineStyle);
	
	painter.setPen(pen);

	QBrush brush(m_fillColor); // 使用填充颜色
	//qDebug() << m_fillColor.name();
	painter.setBrush(brush);
	
	painter.drawEllipse(m_boundingRect);//这里利用绘画椭圆的方法，在矩形内绘画出原型
}

void KCircle::moveTopLeft(QPoint pos)
{
	m_boundingRect.setTopLeft(pos);
	KShape::moveTopLeft(pos);
}

void KCircle::moveTop(QPoint pos)
{
	m_boundingRect.setTop(pos.y());
	KShape::moveTop(pos);
}

void KCircle::moveTopRight(QPoint pos)
{
	m_boundingRect.setTopRight(pos);
	KShape::moveTopRight(pos);
}

void KCircle::moveLeft(QPoint pos)
{
	m_boundingRect.setLeft(pos.x());
	KShape::moveLeft(pos);
}

void KCircle::moveRight(QPoint pos)
{
	m_boundingRect.setRight(pos.x());
	KShape::moveRight(pos);
}

void KCircle::moveBottomLeft(QPoint pos)
{
	m_boundingRect.setBottomLeft(pos);
	KShape::moveBottomLeft(pos);
}

void KCircle::moveBottom(QPoint pos)
{
	m_boundingRect.setBottom(pos.y());
	KShape::moveBottom(pos);
}

void KCircle::moveBottomRight(QPoint pos)
{
	m_boundingRect.setBottomRight(pos);
	KShape::moveBottomRight(pos);
}

KGlobalData::KDrawFlag KCircle::getDrawFlag()
{
	return m_drawFlag;
}

void KCircle::setDrawFlag(KGlobalData::KDrawFlag drawFlag)
{
	m_drawFlag = drawFlag;
}

void KCircle::setSideWidth(double width)
{
	m_lineWidth = width;
}

void KCircle::setFilColor(QString color)
{
	//
	qDebug() << color;
	
	m_fillColor = QColor(color);
}

void KCircle::setLineColor(QString lineColor)
{
	m_lineColor = QColor(lineColor);
}

void KCircle::setLineStyle(Qt::PenStyle lineStyle)
{
	m_lineStyle = lineStyle;
}

void KCircle::setScale(qreal scale)
{
	m_scale = scale;

	QPoint newStartPoint = m_startPoint * m_scale;
	QPoint newEndPoint = m_endPoint * m_scale;

	m_boundingRect = QRect(newStartPoint, newEndPoint).normalized();

}

void KCircle::drawShape(QPainter* painter) //为了保存多个图片到本地的svg
{
	painter->setRenderHint(QPainter::Antialiasing);
	QPen pen;
	pen.setColor(m_lineColor);
	pen.setWidthF(m_lineWidth);
	pen.setStyle(m_lineStyle);
	painter->setPen(pen);
	QBrush brush(m_fillColor);
	painter->setBrush(brush);
	painter->drawEllipse(m_boundingRect);
}

