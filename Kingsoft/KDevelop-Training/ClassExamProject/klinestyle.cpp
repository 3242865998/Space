#include "klinestyle.h"
#include <qDebug>

KLineSytleBox::KLineSytleBox(const QString& title, const Qt::PenStyle, QWidget* parent)
	: KParamBox(title, parent)
	, m_pLineStyleBtn(Q_NULLPTR)
{
	m_pLineStyleBtn = new QComboBox(this);
	m_pLineStyleBtn->setMaximumSize(70, 50);
	m_pLineStyleBtn->addItem(" solid", static_cast<int>(Qt::SolidLine));
	m_pLineStyleBtn->addItem("  Dash", static_cast<int>(Qt::DashLine));
	m_pLineStyleBtn->addItem("  Dot", static_cast<int>(Qt::DotLine));
	QString rgbColorStr = "000000"; // 黑色背景
	m_pLineStyleBtn->setStyleSheet(QString("QComboBox { "
		"border-width: 0px; "
		"border-style: solid; "
		"border-color: black; "
		"background-color: #%1; "
		"padding: 0px; "
		"margin: 0px; "
		"color: white;"
		"}"
		"QComboBox::drop-down { "
		"border-width: 0px; "
		"}"
		"QComboBox QAbstractItemView { "
		"border: 1px solid black; "
		"selection-background-color: lightgray; "
		"background-color: black; "
		"color: white;"
		"}")
		.arg(rgbColorStr));
	m_pVLayout->addWidget(m_pLineStyleBtn); // 添加到布局器

	//(void)connect(m_pLineStyleBtn, &QPushButton::clicked, this, &KLineSytleBox::showPickColorDlg);


}


KLineSytleBox::~KLineSytleBox()
{

}

QComboBox* KLineSytleBox::getLineStyleButton() const
{
	return m_pLineStyleBtn;
}



