#include "kcanvasparamsbar.h"

KCanvasParamsBar::KCanvasParamsBar(const QString& title, QWidget* parent)
	: KParamsBar(title, parent)
	, m_pWidthBox(Q_NULLPTR)
	, m_pHeightBox(Q_NULLPTR)
	, m_pColorBox(Q_NULLPTR)
	, m_pScale(Q_NULLPTR)
	, m_pSideWidth(Q_NULLPTR)
	, m_pShapeColor(Q_NULLPTR)
	, m_pSideColor(Q_NULLPTR)
{
	m_pWidthBox = new KValueBox(QStringLiteral("画布宽度"), KGlobalData::getGlobalDataIntance()->getCanvasWidth(), this);
	m_pHeightBox = new KValueBox(QStringLiteral("画布高度"), KGlobalData::getGlobalDataIntance()->getCanvasHeight(), this);
	m_pColorBox = new KColorBox(QStringLiteral("画布颜色"), KGlobalData::getGlobalDataIntance()->getCanvasColor(), this);
	
	//需要去设计比例变量	
	m_pScale = new KValueBox(QStringLiteral("缩放比例"), KGlobalData::getGlobalDataIntance()->getCanvasScale(), this);
	m_pSideWidth = new KValueBox(QStringLiteral("边框宽度"), KGlobalData::getGlobalDataIntance()->getSideWidth(), this);
	m_pShapeColor = new KColorBox(QStringLiteral("填充颜色"), KGlobalData::getGlobalDataIntance()->getShapeColor(), this);
	m_pSideColor = new KColorBox(QStringLiteral("边框颜色"), KGlobalData::getGlobalDataIntance()->getSideColor(), this);
	m_pLineStyle = new KLineSytleBox(QStringLiteral("边框样式"), KGlobalData::getGlobalDataIntance()->getLineStyle(), this);
	// 添加到网格布局
	m_pGridLayout->addWidget(m_pWidthBox, 0, 0);// 第 0 行 第 0 列
	m_pGridLayout->addWidget(m_pHeightBox, 0, 1);// 第 0 行 第 1 列
	m_pGridLayout->addWidget(m_pColorBox, 1, 1);
	m_pGridLayout->addWidget(m_pScale, 1, 0);
	m_pGridLayout->addWidget(m_pSideWidth, 2, 0);
	m_pGridLayout->addWidget(m_pLineStyle, 2, 1);
	m_pGridLayout->addWidget(m_pShapeColor, 3, 0);
	m_pGridLayout->addWidget(m_pSideColor, 3, 1);
}

KCanvasParamsBar::~KCanvasParamsBar()
{
}
