#ifndef __K_TEXT_H__
#define __K_TEXT_H__

#include "kshape.h"
#include <QWidget>
#include <QLineEdit>

class KText : public KShape
{
	Q_OBJECT

public:
	KText(QObject* parent = Q_NULLPTR);
	~KText();

	void setStartPoint(const QPoint& point);
	void setEndPoint(const QPoint& point);
	void move(QPoint offset) override;
	

	void showTextBox(QWidget* parent);
	virtual void drawShape(QPaintDevice* parent = Q_NULLPTR) override;


	void setScale(qreal scale) override;
	//为了保存多个图片
	void drawShape(QPainter* painter) override;

	KGlobalData::KDrawFlag getDrawFlag() override;
	void setDrawFlag(KGlobalData::KDrawFlag drawFlag) override;

private:
	QPoint m_startPoint;
	QLineEdit* m_textBox;
};

#endif
