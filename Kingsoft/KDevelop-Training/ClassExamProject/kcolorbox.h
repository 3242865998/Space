#ifndef __K_PARAMBOX_H_
#define __K_PARAMBOX_H_

#include <QPushButton>
#include <QColorDialog>

#include "kparambox.h"

class KColorBox : public KParamBox
{
	Q_OBJECT

public:
	KColorBox(const QString &title,const QString &rgbColorStr,
		QWidget *parent);
	~KColorBox();

	// 鼠标释放事件,鼠标释放时弹出颜色选择对话框
	virtual void mouseReleaseEvent(QMouseEvent* event) override;


	

	QPushButton* getColorButton() const;

	void shapeColorChanged();
	void lineColorChanged();
signals:
	void pickedColor();
	void shapeColor(QString shapeColor);
signals:
	void lineColor(QString lineColor);



private slots:
	void showPickColorDlg();
private:
	QPushButton* m_pColorBtn;
};

#endif
