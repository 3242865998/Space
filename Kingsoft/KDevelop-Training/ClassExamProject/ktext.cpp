#include "ktext.h"
#include <QPainter>
#include <QLineEdit>
#include <QEvent>
#include <qDebug>
#include <QMouseEvent>
KText::KText(QObject* parent)
	: KShape(parent), m_textBox(Q_NULLPTR)
{
	m_drawFlag = KGlobalData::KDrawFlag::TextDrawFlag;//为了复制，得到这个，让工厂重新做一个
}

KText::~KText()
{
	if (m_textBox)
	{
		delete m_textBox;
	}
}

void KText::setStartPoint(const QPoint& point)
{
	m_startPoint = point;
	
}



void KText::move(QPoint offset)
{

	m_startPoint += offset;

	qDebug() << "Text shape moved to: " << m_startPoint;
}



void KText::showTextBox(QWidget* parent)
{
	if (!m_textBox)
	{
		m_textBox = new QLineEdit(parent);
		m_textBox->setGeometry(QRect(m_startPoint * m_scale, QSize(100, 30))); // Default size of 100x30
		m_textBox->setStyleSheet("background: transparent; border: none;"); // 设置背景透明，移除边框
		m_textBox->setFocus();
		m_textBox->show();

	}
	
}

void KText::drawShape(QPaintDevice* parent)
{
	if (m_textBox)
	{
		QPainter painter(parent);

		painter.drawRect(m_textBox->geometry());
		//painter.drawText(m_textBox->geometry(), Qt::AlignLeft, m_textBox->text());//防止重影子文本呢
	
	}
}

void KText::setScale(qreal scale)
{
	m_scale = scale;
}

void KText::drawShape(QPainter* painter)
{
	

	painter->drawRect(m_textBox->geometry());
}

KGlobalData::KDrawFlag KText::getDrawFlag()
{
	return m_drawFlag;
}

void KText::setDrawFlag(KGlobalData::KDrawFlag drawFlag)
{
	m_drawFlag = drawFlag;
}
