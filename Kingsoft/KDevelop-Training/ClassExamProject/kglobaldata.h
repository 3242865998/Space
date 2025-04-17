#ifndef __K_GLOBAL_DATA__
#define __K_GLOBAL_DATA__

#include <QObject>

class KGlobalData : public QObject
{
	Q_OBJECT

public:
	enum class KDrawFlag
	{
		NoneDrawFlag = 0,
		MouseDrawFlag,
		PenDrawFlag,
		LineDrawFlag,
		RectDrawFlag,
		CircleDrawFlag,
		TextDrawFlag,
		FiveDrawFlag,
		SixDrawFlag,
		StarDrawFlag
	};

	KGlobalData(QObject *parent = Q_NULLPTR);
	~KGlobalData();

	static KGlobalData *getGlobalDataIntance();

	void setDrawFlag(KGlobalData::KDrawFlag drawflag);
	KDrawFlag getDrawFlag();

	void setCanvasWidth(const int width);
	void setCanvasHeight(const int height);

	int getCanvasWidth() const;
	int getCanvasHeight() const;

	void setCanvasColor(const QString & colorStr);
	QString getCanvasColor();

	void setCanvaScale(qreal scale);
	qreal getCanvasScale();

	//自己加的各图形属性
	void setSideWidth(int width);
	double getSideWidth() const;

	void setShapeColor(const QString& colorStr);
	QString getShapeColor() const;

	void setSideColor(const QString& colorStr);
	QString getSideColor() const;

	void setLineStyle(Qt::PenStyle lineSytle);
	Qt::PenStyle getLineStyle() const;

private:
	KGlobalData(const KGlobalData &other) = delete;
	KGlobalData(const KGlobalData &&other) = delete;
	void operator=(const KGlobalData) = delete;

	KDrawFlag m_drawFlag;
	
	int m_canvasWidth;
	int m_canvasHeight;
	QString m_canvasColor;
	
	qreal m_scale;

	//自己加的
	double m_sideWidth;
	QString m_shapeColor;
	QString m_sideColor;
	Qt::PenStyle m_lineStyle;
};


#endif
