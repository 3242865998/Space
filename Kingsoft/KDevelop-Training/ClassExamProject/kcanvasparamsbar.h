#ifndef __K_CANVAS_PARAMS_BAR_H_
#define __K_CANVAS_PARAMS_BAR_H_

#include "kparamsbar.h"
#include "kcolorbox.h"
#include "kvaluebox.h"
#include "klinestyle.h"
class KCanvasParamsBar : public KParamsBar
{
	Q_OBJECT
	friend class KMainWindow;
public:
	KCanvasParamsBar(const QString &title,QWidget *parent);
	~KCanvasParamsBar();

	
private:
	KValueBox *m_pWidthBox;
	KValueBox *m_pHeightBox;
	KColorBox *m_pColorBox;

	KValueBox* m_pScale;
	KValueBox* m_pSideWidth;
	KColorBox* m_pShapeColor;
	KColorBox* m_pSideColor;
	KLineSytleBox* m_pLineStyle;
	
};

#endif
