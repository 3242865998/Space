#include "kglobaldata.h"
#include <Windows.h>


KGlobalData::KGlobalData(QObject *parent)
	: QObject(parent)
	,m_drawFlag(KDrawFlag::NoneDrawFlag)
    ,m_canvasColor("FFFFFF")
    ,m_canvasWidth(600)
    ,m_canvasHeight(400)
    ,m_scale(1)
    //person
	,m_sideWidth(1.5)  
	,m_shapeColor("FFFFFF")  
	,m_sideColor("000000")
    ,m_lineStyle(Qt::SolidLine)
    //person
{
}

//person
void KGlobalData::setSideWidth(int width) {
	m_sideWidth = width;
}

double KGlobalData::getSideWidth() const 
{
	return m_sideWidth;
}

void KGlobalData::setShapeColor(const QString& colorStr)
{
	m_shapeColor = colorStr;
}

QString KGlobalData::getShapeColor() const 
{
	return m_shapeColor;
}

void KGlobalData::setSideColor(const QString& colorStr) 
{
	m_sideColor = colorStr;
}

QString KGlobalData::getSideColor() const 
{
	return m_sideColor;
}
void KGlobalData::setLineStyle(Qt::PenStyle lineSytle)
{
    m_lineStyle = lineSytle;
}
Qt::PenStyle KGlobalData::getLineStyle() const 
{
	return m_lineStyle;
}

//person


KGlobalData *KGlobalData::getGlobalDataIntance()
{
    static KGlobalData s_instance;
    static KGlobalData* pinstance = nullptr;
    if (pinstance == nullptr)
        pinstance = &s_instance;
    return pinstance;
}

void KGlobalData::setDrawFlag(KGlobalData::KDrawFlag drawflag)
{
    this->m_drawFlag = drawflag;
}

KGlobalData::KDrawFlag KGlobalData::getDrawFlag()
{
	return m_drawFlag;

}
void KGlobalData::setCanvasWidth(const int width)
{
    this->m_canvasWidth = width;
}

void KGlobalData::setCanvasHeight(const int height)
{
    this->m_canvasHeight = height;
}

int KGlobalData::getCanvasWidth() const
{
    return this->m_canvasWidth;
}

int KGlobalData::getCanvasHeight() const
{
    return m_canvasHeight;
}

void KGlobalData::setCanvasColor(const QString& colorStr)
{
    this->m_canvasColor = colorStr;
}

QString KGlobalData::getCanvasColor()
{
    return m_canvasColor;
}

void KGlobalData::setCanvaScale(qreal scale)
{
    m_scale = scale;
    
}

qreal KGlobalData::getCanvasScale()
{
    return m_scale;
}

KGlobalData::~KGlobalData()
{
}
