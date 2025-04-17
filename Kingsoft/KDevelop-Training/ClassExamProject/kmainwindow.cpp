#include "kmainwindow.h"
#include <QLineEdit>
#include <QShortcut>
#include <QKeySequence>
#include <QKeyEvent>
KMainWindow::KMainWindow(QWidget *parent)
    : QWidget(parent)
    ,m_pVLayout(Q_NULLPTR)
    ,m_pHLayout(Q_NULLPTR)
    ,m_pSvgMainWin(Q_NULLPTR)
    ,m_pToolBar(Q_NULLPTR)
	
{
    ui.setupUi(this);
    initWindows();
    initConnection();

}


void KMainWindow::initWindows()//把三大块准备好
{
	m_pVLayout = new QVBoxLayout(this);
	m_pVLayout->setSpacing(0);
	m_pVLayout->setMargin(0);

	m_pHLayout = new QHBoxLayout(this);
	m_pHLayout->setSpacing(0);

    m_pToolBar = new KToolBar(this);
    m_pSvgMainWin = new KSvgMainWindow(this);
    m_pCanvasParamsBar = new KCanvasParamsBar(QStringLiteral("画布"),this);

	KFileMenu* fileMenu = new KFileMenu(this);
	m_pVLayout->setMenuBar(fileMenu);
    
   
    
	

    m_pHLayout->addWidget(m_pToolBar);
    m_pHLayout->addWidget(m_pSvgMainWin);
    m_pHLayout->addWidget(m_pCanvasParamsBar);

    m_pVLayout->addLayout(m_pHLayout);
    
	;
    setLayout(m_pVLayout);
 }
        
void KMainWindow::initConnection()
{    //负责处理中间画布的大小颜色的连接
    (void)connect(m_pCanvasParamsBar->m_pWidthBox->m_pParamEdit, &QLineEdit::editingFinished, this, &KMainWindow::validateCanvasParams);
    (void)connect(m_pCanvasParamsBar->m_pHeightBox->m_pParamEdit, &QLineEdit::editingFinished, this, &KMainWindow::validateCanvasParams);
    (void)connect(m_pCanvasParamsBar->m_pColorBox, &KColorBox::pickedColor, this, &KMainWindow::validateCanvasParams);
   //线宽
    (void)connect(this, &KMainWindow::handleSideWidthChanged,m_pSvgMainWin, &KSvgMainWindow::sideWidthHandle);
    (void)connect(m_pCanvasParamsBar->m_pSideWidth->m_pParamEdit, &QLineEdit::editingFinished, this, &KMainWindow::changedSideWidth);
    //填充颜色
	(void)connect(this, &KMainWindow::handleShapeColorChanged, m_pSvgMainWin, &KSvgMainWindow::shapeColorHandle);
	(void)connect(m_pCanvasParamsBar->m_pShapeColor->getColorButton(), &QPushButton::clicked, m_pCanvasParamsBar->m_pShapeColor, &KColorBox::shapeColorChanged);
    (void)connect(m_pCanvasParamsBar->m_pShapeColor, &KColorBox::shapeColor, this, &KMainWindow::changedShapeColor);
	//边框颜色
	(void)connect(this, &KMainWindow::handleLineColorChanged, m_pSvgMainWin, &KSvgMainWindow::lineColorHandle);
	(void)connect(m_pCanvasParamsBar->m_pSideColor->getColorButton(), &QPushButton::clicked, m_pCanvasParamsBar->m_pSideColor, &KColorBox::lineColorChanged);
	(void)connect(m_pCanvasParamsBar->m_pSideColor, &KColorBox::lineColor, this, &KMainWindow::changedLineColor);
	//边框样式
	(void)connect(m_pCanvasParamsBar->m_pLineStyle->getLineStyleButton(), QOverload<int>::of(&QComboBox::currentIndexChanged), m_pSvgMainWin, &KSvgMainWindow::lineStyleHandle);

    //scale
    //(void)connect(m_pCanvasParamsBar->m_pScale->m_pParamEdit, &QLineEdit::editingFinishe);
    (void)connect(m_pSvgMainWin, &KSvgMainWindow::scaleChanged, m_pCanvasParamsBar->m_pScale, &KValueBox::setScaleValue);
    (void)connect(m_pSvgMainWin, &KSvgMainWindow::canvasChanged, m_pCanvasParamsBar->m_pWidthBox, &KValueBox::setWidthScaleValue);
    (void)connect(m_pSvgMainWin, &KSvgMainWindow::canvasChanged, m_pCanvasParamsBar->m_pHeightBox, &KValueBox::setHeightScaleValue);
    (void)connect(m_pCanvasParamsBar->m_pScale->m_pParamEdit, &QLineEdit::editingFinished, this, &KMainWindow::resizeCanvas);
    (void)connect(this, &KMainWindow::editScale, m_pSvgMainWin, &KSvgMainWindow::changedSizeSScaleCanvas);
    (void)connect(m_pCanvasParamsBar->m_pScale->m_pParamEdit, &QLineEdit::textChanged, m_pSvgMainWin, &KSvgMainWindow::scaleShapeHandle);

    //新建文件
    (void)connect(this, &KMainWindow::toSvgMainWindowNewFile, m_pSvgMainWin, &KSvgMainWindow::newFile);
    //保存到本地
    (void)connect(this, &KMainWindow::toSvgMainWindowSave, m_pSvgMainWin, &KSvgMainWindow::saveFile);
    //打开本地svg
    (void)connect(this, &KMainWindow::toSvgMainWindowOpen, m_pSvgMainWin, &KSvgMainWindow::openLocalSvg);
	//导出为PNG
	(void)connect(this, &KMainWindow::toSvgMainWindowexportPNG, m_pSvgMainWin, &KSvgMainWindow::exportSvgToPNG);
}

void KMainWindow::changedSideWidth()
{
    emit handleSideWidthChanged(m_pCanvasParamsBar->m_pSideWidth->m_pParamEdit->text().toDouble());
}

void KMainWindow::changedShapeColor(QString shapeColor)
{
    emit handleShapeColorChanged(shapeColor);
}
void KMainWindow::changedLineColor(QString lineColor)
{
	emit handleLineColorChanged(lineColor);
}


void KMainWindow::validateCanvasParams()
{
    qint32 width = m_pCanvasParamsBar->m_pWidthBox->m_pParamEdit->text().toInt();
    qint32 height = m_pCanvasParamsBar->m_pHeightBox->m_pParamEdit->text().toInt();

    KGlobalData::getGlobalDataIntance()->setCanvasWidth(width);
    KGlobalData::getGlobalDataIntance()->setCanvasHeight(height);
    
    m_pSvgMainWin->m_pCanvas->resize(width, height);
    m_pSvgMainWin->m_pCanvas->setStyleSheet(QString("background-color:#%1").arg(KGlobalData::getGlobalDataIntance()->getCanvasColor()));
   
    
    //
    m_pCanvasParamsBar->m_pScale->m_pParamEdit->setText("1");
    KGlobalData::getGlobalDataIntance()->setCanvaScale(1);
}
//
void KMainWindow::resizeCanvas()
{
    qint32 scale = m_pCanvasParamsBar->m_pScale->m_pParamEdit->text().toDouble();
    KGlobalData::getGlobalDataIntance()->setCanvaScale(scale);
    emit editScale(scale);
}

void KMainWindow::newFile()
{
    emit toSvgMainWindowNewFile();
}


void KMainWindow::saveSvgToLocal()
{
	emit toSvgMainWindowSave();
}

void KMainWindow::openSVG()
{
    emit toSvgMainWindowOpen();
}

void KMainWindow::exportPNG()
{
    emit toSvgMainWindowexportPNG();
}
