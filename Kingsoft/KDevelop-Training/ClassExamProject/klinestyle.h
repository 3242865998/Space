#ifndef __K_LINE_STYLE_H__
#define __K_LINE_STYLE_H__

#include <QComboBox>
#include <QColorDialog>

#include "kparambox.h"

class KLineSytleBox : public KParamBox
{
	Q_OBJECT

public:
	KLineSytleBox(const QString& title, const Qt::PenStyle,
		QWidget* parent);
	~KLineSytleBox();

	
	




	QComboBox* getLineStyleButton() const;

	
signals:




private slots:
	
private:
	QComboBox* m_pLineStyleBtn;
};

#endif
