#include "kpen.h"
#include <QPainterPath>
#include <QtMath>
#include <qDebug>
KPen::KPen(QObject* parent)
	:KShape(parent)
{
	m_drawFlag = KGlobalData::KDrawFlag::PenDrawFlag;//为了复制，得到这个，让工厂重新做一个
}
KPen::~KPen()
{
}
void KPen::setStartPoint()
{
	QPoint m_minXPoint, m_maxXPoint, m_minYPoint, m_maxYPoint;
	int minX = std::numeric_limits<int>::max();
	int maxX = std::numeric_limits<int>::min();
	int minY = std::numeric_limits<int>::max();
	int maxY = std::numeric_limits<int>::min();

	for (const QPoint& point : m_posVector)
	{
		if (point.x() < minX)
		{
			minX = point.x();
			m_minXPoint = point;
		}
		if (point.x() > maxX)
		{
			maxX = point.x();
			m_maxXPoint = point;
		}
		if (point.y() < minY)
		{
			minY = point.y();
			m_minYPoint = point;
		}
		if (point.y() > maxY)
		{
			maxY = point.y();
			m_maxYPoint = point;
		}
	}

	m_startPoint.rx() = m_minXPoint.x();
	m_startPoint.ry() = m_minYPoint.y();

}
void KPen::setEndPoint()
{
	QPoint m_minXPoint, m_maxXPoint, m_minYPoint, m_maxYPoint;
	int minX = std::numeric_limits<int>::max();
	int maxX = std::numeric_limits<int>::min();
	int minY = std::numeric_limits<int>::max();
	int maxY = std::numeric_limits<int>::min();

	for (const QPoint& point : m_posVector)
	{
		if (point.x() < minX)
		{
			minX = point.x();
			m_minXPoint = point;
		}
		if (point.x() > maxX)
		{
			maxX = point.x();
			m_maxXPoint = point;
		}
		if (point.y() < minY)
		{
			minY = point.y();
			m_minYPoint = point;
		}
		if (point.y() > maxY)
		{
			maxY = point.y();
			m_maxYPoint = point;
		}
	}

	m_endPoint.rx() = m_maxXPoint.x();
	m_endPoint.ry() = m_maxYPoint.y();
	
}
void KPen::addPos(const QPoint& pos)
{
	if (m_posVector.isEmpty())
	{
		m_startPoint = pos;
		m_endPoint = pos;
	}
	else
	{
		if (pos.x() < m_startPoint.x())//即重新设置开始的位置，而终点变为开始的位置
			m_startPoint.rx() = pos.x();
		if (pos.y() < m_startPoint.y())
			m_startPoint.ry() = pos.y();
		if (pos.x() > m_endPoint.x())
			m_endPoint.rx() = pos.x();
		if (pos.y() > m_endPoint.y())
			m_endPoint.ry() = pos.y();
	}
	//不管怎么样，要记录下路径上的所有点，后来要绘制
	m_posVector.append(pos);

	
}

void KPen::move(QPoint offset)//选中时候移动偏移量offset
{
	for (int i = 0; i < m_posVector.size(); i++)
	{
		m_posVector[i] += offset;
	}
	KShape::move(offset);
	
}

KShapeType KPen::getShapeType()
{
	return KShapeType::PenShapeType;
}

void KPen::drawShape(QPaintDevice* parent)
{
	QPainter painter(parent);
	QPainterPath path;
	painter.setRenderHint(QPainter::Antialiasing);
	auto pos = m_posVector.begin();

	//path.moveTo(*pos);//这个的目的是把线的开始点移动到这里
	path.moveTo(*pos * m_scale);
	while (pos != m_posVector.end())//加入所有点的路径
	{
		path.lineTo(*pos * m_scale);
		pos++;
	}
	QPen pen;
	pen.setColor(m_lineColor);
	pen.setWidthF(m_lineWidth);

	pen.setStyle(m_lineStyle);

	painter.setPen(pen);
	QBrush brush(m_fillColor);
	painter.setBrush(brush);

	painter.drawPath(path);
	
}




void KPen::setSideWidth(double width)
{
	m_lineWidth = width;
}

void KPen::setFilColor(QString color)
{
	m_fillColor = QColor(color);
}

void KPen::setLineColor(QString lineColor)
{
	m_lineColor = QColor(lineColor);
}

void KPen::setLineStyle(Qt::PenStyle lineStyle)
{
	m_lineStyle = lineStyle;
}

void KPen::setScale(qreal scale)
{
	m_scale = scale;
}

void KPen::drawShape(QPainter* painter)
{
	
	QPainterPath path;
	painter->setRenderHint(QPainter::Antialiasing);
	auto pos = m_posVector.begin();

	//path.moveTo(*pos);//这个的目的是把线的开始点移动到这里
	path.moveTo(*pos * m_scale);

	//while (pos != m_posVector.end())//加入所有点的路径
	//{
	//	path.lineTo(*pos);
	//	pos++;
	//}
	while (pos != m_posVector.end())//加入所有点的路径
	{
		path.lineTo(*pos * m_scale);
		pos++;
	}
	QPen pen;
	pen.setColor(m_lineColor);
	pen.setWidthF(m_lineWidth);

	pen.setStyle(m_lineStyle);

	painter->setPen(pen);
	QBrush brush(m_fillColor);
	painter->setBrush(brush);

	painter->drawPath(path);
}

void KPen::setPoints(QVector<QPoint> posVector)
{
	m_posVector = posVector;
	for (auto& pos : m_posVector)//复制粘贴偏移量，因为pen不是依赖于起始点和终点绘制，所以需要在这里设置偏移量
	{
		pos = pos + QPoint(10, 10);
	}
}

QVector<QPoint> KPen::getPoints()
{
	return m_posVector;
}

KGlobalData::KDrawFlag KPen::getDrawFlag()
{
	return m_drawFlag;
}

void KPen::setDrawFlag(KGlobalData::KDrawFlag drawFlag)
{
	m_drawFlag = drawFlag;
}
