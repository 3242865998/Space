#include "kcanvas.h"
#include "kshapefactory.h"
#include "kcanvasparamsbar.h"
#include <QMouseEvent>
#include <QDebug>
#include <QObject>	
#include <QInputDialog>

#include <QSvgGenerator>//用来保存svg到本地
#include <QDir>//保存到本地
#include <QFileDialog>//保存到本地




KCanvas::KCanvas(QWidget* parent)
	: QWidget(parent)
	, m_pCurrentShape(Q_NULLPTR)
	, m_TransType(KTransType::None)
	, m_isDrawing(false)
	, m_isLPress(false)
	, m_isSelected(false)
	, m_svgRenderer(nullptr) // 为了从本地打开svg
	, m_rightMenu (nullptr)
	
{
	setAttribute(Qt::WA_StyledBackground, true);

	// 设置背景颜色为白色
	setStyleSheet("background-color:#FFFFFF");

	KGlobalData::getGlobalDataIntance()->setCanvasColor("FFFFFF");
	resize(KGlobalData::getGlobalDataIntance()->getCanvasWidth(),
		KGlobalData::getGlobalDataIntance()->getCanvasHeight());

	setMouseTracking(true);//设置鼠标追踪
	setFocusPolicy(Qt::ClickFocus);// 单击获取焦点

	initConnet();

	saveState();  // 保存初始状态
}

KCanvas::~KCanvas()
{
	//for (auto shape : m_pShapeList)
	//	qInfo() << "add:" << shape;
	
	for (auto shape : m_pShapeList)
	{
		delete shape;
	}
	if(!m_pEverAllSelected)
	for (auto shape : m_pSelectedShapes)
	{
		delete shape;
	}
	m_pShapeList.clear();
	m_pSelectedShapes.clear();
}

void KCanvas::keyPressEvent(QKeyEvent* event)
{
	if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_A)
	{
		handleSelectAll();
	}
	else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Z)
	{
		handleUndo();
	}
	else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Y)
	{
		handleRedo();
	}
	else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_X)
	{
		handleCut();
	}
	else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_C)
	{
		handleCopy();
	}
	else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_V)
	{
		handlePaste();
	}
	else if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace)
	{
		handleDelete();
	}
	else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_D)
	{
		handleOverwrite();
	}
	else if (event->key() == Qt::Key_Up)
	{
		handleMoveUp();
	}
	else if (event->key() == Qt::Key_Down)
	{
		handleMoveDown();
	}
	else if (event->key() == Qt::Key_Left)
	{
		handleMoveToBack();
	}
	else if (event->key() == Qt::Key_Right)
	{
		handleMoveToFront();
	}
}
void KCanvas::initConnet()
{
	(void)connect(m_rightMenu, &KRightMenu::toCanvasHandleDelete, this, &KCanvas::handleDelete);
	(void)connect(m_rightMenu, &KRightMenu::toCanvasHandleCopy, this, &KCanvas::handleCopy);
	(void)connect(m_rightMenu, &KRightMenu::toCanvasHandlePaste, this, &KCanvas::handlePaste);
	(void)connect(m_rightMenu, &KRightMenu::toCanvasHandleOverwrite, this, &KCanvas::handleOverwrite);
	(void)connect(m_rightMenu, &KRightMenu::toCanvasHandleCut, this, &KCanvas::handleCut);
	(void)connect(m_rightMenu, &KRightMenu::toCanvasHandleMoverUp, this, &KCanvas::handleMoveUp);
	(void)connect(m_rightMenu, &KRightMenu::toCanvasHandleMoveDown, this, &KCanvas::handleMoveDown);
	(void)connect(m_rightMenu, &KRightMenu::toCanvasHandleMoveToFront, this, &KCanvas::handleMoveToFront);
	(void)connect(m_rightMenu, &KRightMenu::toCanvasHandleMoveToBack, this, &KCanvas::handleMoveToBack);
	(void)connect(m_rightMenu, &KRightMenu::toCanvasHandleUndo, this, &KCanvas::handleUndo);
	(void)connect(m_rightMenu, &KRightMenu::toCanvasHandleRedo, this, &KCanvas::handleRedo);
	(void)connect(m_rightMenu, &KRightMenu::toCanvasHandleSelectAll, this, &KCanvas::handleSelectAll);
}
	void KCanvas::saveState()
	{
		// 在进行新的操作时，清空重做栈，因为重做历史已无效,只能redo一次
		m_redoStack.clear();
		// 深拷贝当前的形状列表
		qInfo() << "m_list: " << m_pShapeList;
		QList<KShape*> currentShapes;
		for (KShape* shape : m_pShapeList)
		{
			qInfo() << "shape: " << shape;
			KShape* tempShape = KShapeFactory::createShape(shape->getDrawFlag());
			tempShape = setShapePersonalityNoOffset(tempShape, shape);//这个函数用来纯纯深拷贝一个对象
			currentShapes.append(tempShape);  // 存放当前的所有图像信息
		}
		m_shapeHistory.append(currentShapes);
	}
	void KCanvas::handleSelectAll()
	{
		// 设置所有图形为选中状态
		m_isAllSelected = true;

		// 清空当前选中状态并选中所有形状
		m_pSelectedShapes.clear();
		for (KShape* shape : m_pShapeList)
		{
			m_pSelectedShapes.append(shape);
			m_pEverAllSelected = true;
		}

		update(); // 更新绘制
	}

	void KCanvas::handleRedo()
	{
		if (!m_redoStack.isEmpty())
		{
			// 保存当前状态到撤销栈
			m_shapeHistory.append(m_pShapeList);

			// 从重做栈中移除最近的状态并恢复
			m_pShapeList = m_redoStack.takeLast();

			// 更新画布
			update();
		}

	}
	void KCanvas::handleUndo()
	{
	

		if (!m_shapeHistory.isEmpty())
		{
			m_redoStack.append(m_pShapeList);
			// 从历史记录中拿出最近的状态
			m_pShapeList = m_shapeHistory.takeLast();
			qInfo() << "m_list" << m_pShapeList;
			// 更新画布
			update();
		}
	}
	void KCanvas::handleDelete()
	{
		//qInfo() << "size: " << m_pShapeList.size();
		if (m_pCurrentShape)  // 检查是否有选中的图形
		{
			m_pShapeList.removeOne(m_pCurrentShape);  // 从列表中移除
			delete m_pCurrentShape;  // 删除对象释放内存
			m_pCurrentShape = nullptr;  // 清除当前选中的图形指针
			update();  // 更新画布
			saveState();//保存当前状态
		}
		//qInfo() << "size: " << m_pShapeList.size();
	
	}
	void KCanvas::handleMoveUp()
	{
		if (m_pCurrentShape)
		{
			// 找到当前选中图形在列表中的索引
			int index = m_pShapeList.indexOf(m_pCurrentShape);

			// 如果当前图形不是第一个元素
			if (index > 0)
			{
				// 将当前图形与前一个图形交换位置
				m_pShapeList.swapItemsAt(index, index - 1);

				// 更新画布，重绘图形
				update();
			}
			saveState();//保存当前状态
		}
	
	}
	void KCanvas::handleMoveToFront()
	{
		if (m_pCurrentShape)
		{
			// 找到当前选中图形在列表中的索引
			int index = m_pShapeList.indexOf(m_pCurrentShape);

			// 如果当前图形不是第一个元素
			if (index != -1 && index > 0)
			{
				//先移除
				m_pShapeList.removeAt(index);
				//在放置在最前
				m_pShapeList.prepend(m_pCurrentShape);

				// 更新画布，重绘图形
				update();
			}

			saveState();//保存当前状态
		}
	
	}
	void KCanvas::handleMoveToBack()
	{
		if (m_pCurrentShape)
		{
			// 找到当前选中图形在列表中的索引
			int index = m_pShapeList.indexOf(m_pCurrentShape);

			// 如果当前图形不是第一个元素
			if (index != -1 && index < m_pShapeList.size() - 1)
			{
				//先移除
				m_pShapeList.removeAt(index);
				//在放置在最前
				m_pShapeList.append(m_pCurrentShape);

				// 更新画布，重绘图形
				update();
			}
			saveState();//保存当前状态
		}
	
	}
	void KCanvas::handleMoveDown()
	{

		if (m_pCurrentShape)
		{
			// 找到当前选中图形在列表中的索引
			int index = m_pShapeList.indexOf(m_pCurrentShape);

			// 如果当前图形不是第一个元素
			if (index < m_pShapeList.size() - 1)
			{
				// 将当前图形与前一个图形交换位置
				m_pShapeList.swapItemsAt(index, index + 1);

				// 更新画布，重绘图形
				update();
			}
			saveState();//保存当前状态
		}
	
	}
	void KCanvas::handleCopy()
	{
		m_pCopyShape.clear();
		if (m_isAllSelected)//是否全选
		{
			for (auto shape : m_pShapeList)
			{
				KShape* tempShape = KShapeFactory::createShape(shape->getDrawFlag());
				tempShape = setShapePersonality(tempShape, shape);
				m_pCopyShape.append(tempShape);
			}
			m_isAllSelected = false;
		}
		else if (m_pCurrentShape)  // 检查是否有选中的图形
		{
			KShape* tempShape = KShapeFactory::createShape(m_pCurrentShape->getDrawFlag());
			tempShape = setShapePersonality(tempShape, m_pCurrentShape);
			m_pCopyShape.append(tempShape);
		}	
	}
	void  KCanvas::handlePaste()
	{
		saveState();//保存当前状态
		if (!m_pCopyShape.isEmpty())
		{
			for (auto shape : m_pCopyShape)
			{
				if (shape)
				{
					if (m_pShapeList.contains(shape)) continue;
					m_pShapeList.prepend(shape);  // 将复制的图形添加到列表中
					m_pCurrentShape = shape;  // 更新当前选中的图形为复制的图形
					update();
				}
			}// 更新画布
			//saveState();//保存当前状态
		}
		m_pCopyShape.clear();
	}
	void KCanvas::handleOverwrite()
	{
		saveState();//保存当前状态
		m_pCopyShape.clear();

		for (auto shape : m_pShapeList)
		{
			KShape* tempShape = KShapeFactory::createShape(shape->getDrawFlag());
			tempShape = setShapePersonality(tempShape, shape);
			m_pCopyShape.append(tempShape);
		}
		for (auto shape : m_pCopyShape)
		{
			if (shape)
			{
				if (m_pShapeList.contains(shape)) continue;
				m_pShapeList.prepend(shape);  // 将复制的图形添加到列表中
				//m_pCurrentShape = shape;  // 更新当前选中的图形为复制的图形
				update();
			}
		}// 更新画布
		m_pCopyShape.clear();
	
		qInfo() << "number state: " << m_shapeHistory.size();
	}
	void KCanvas::handleCut()
	{
		m_pCopyShape.clear();
		if (m_isAllSelected)//是否全选
		{
			for (auto shape : m_pShapeList)
			{
				KShape* tempShape = KShapeFactory::createShape(shape->getDrawFlag());
				tempShape = setShapePersonality(tempShape, shape);
				m_pCopyShape.append(tempShape);
			}
			m_isAllSelected = false;
		}
		else if (m_pCurrentShape)  // 检查是否有选中的图形
		{
			KShape* tempShape = KShapeFactory::createShape(m_pCurrentShape->getDrawFlag());
			tempShape = setShapePersonalityNoOffset(tempShape, m_pCurrentShape);
			m_pCopyShape.append(tempShape);
		}
		handleDelete();
		saveState();//保存当前状态
	}
	KShape* KCanvas::setShapePersonality(KShape* tempShape,KShape* mainShape)
	{
		tempShape->setStartPoint(mainShape->getStartPoint() + QPoint(10, 10));
		tempShape->setEndPoint(mainShape->getEndPoint() + QPoint(10, 10));
		tempShape->setLineColor(mainShape->getLineColor());
		tempShape->setDrawFlag(mainShape->getDrawFlag());
		//qInfo() << "      " << m_pCurrentShape->getFilColor();
		tempShape->setFilColor(mainShape->getFilColor());
		tempShape->setScale(mainShape->getScale());
		tempShape->setSideWidth(mainShape->getSideWidth());
		tempShape->setLineStyle(mainShape->getLineStyle());
		if (mainShape->getDrawFlag() == KGlobalData::KDrawFlag::StarDrawFlag ||
			mainShape->getDrawFlag() == KGlobalData::KDrawFlag::FiveDrawFlag ||
			mainShape->getDrawFlag() == KGlobalData::KDrawFlag::SixDrawFlag
			)
		{
			tempShape->setBoundingRect(mainShape->getBoundingRect());
			//tempShape->setPoints(mainShape->getPoints());

		}
		if (mainShape->getDrawFlag() == KGlobalData::KDrawFlag::PenDrawFlag)
		{
			tempShape->setPoints(mainShape->getPoints());
		}
		//m_pCopyShape.append(tempShape);
		return tempShape;
	}

	KShape* KCanvas::setShapePersonalityNoOffset(KShape* tempShape, KShape* mainShape)
	{
		tempShape->setStartPoint(mainShape->getStartPoint());
		tempShape->setEndPoint(mainShape->getEndPoint() );
		tempShape->setLineColor(mainShape->getLineColor());
		tempShape->setDrawFlag(mainShape->getDrawFlag());
		//qInfo() << "      " << m_pCurrentShape->getFilColor();
		tempShape->setFilColor(mainShape->getFilColor());
		tempShape->setScale(mainShape->getScale());
		tempShape->setSideWidth(mainShape->getSideWidth());
		tempShape->setLineStyle(mainShape->getLineStyle());
		if (mainShape->getDrawFlag() == KGlobalData::KDrawFlag::StarDrawFlag ||
			mainShape->getDrawFlag() == KGlobalData::KDrawFlag::FiveDrawFlag ||
			mainShape->getDrawFlag() == KGlobalData::KDrawFlag::SixDrawFlag
			)
		{
			tempShape->setBoundingRect(mainShape->getBoundingRect());
			//tempShape->setPoints(mainShape->getPoints());

		}
		if (mainShape->getDrawFlag() == KGlobalData::KDrawFlag::PenDrawFlag)
		{
			tempShape->setPoints(mainShape->getPoints());
		}
		//m_pCopyShape.append(tempShape);
		return tempShape;
	}
void KCanvas::onSideWidthChanged(double lineWidth)
{
	if (m_pCurrentShape)
	{
		m_pCurrentShape->setSideWidth(lineWidth);
		update();saveState();//保存当前状态
		saveState();//保存当前状态
	}
}

void KCanvas::onShapeColorChanged(QString shapeColor)
{
	if (m_pCurrentShape)
	{
		m_pCurrentShape->setFilColor(shapeColor);
		update();
		saveState();//保存当前状态
	}
}

void KCanvas::onLineColorChanged(QString lineColor)
{
	if (m_pCurrentShape)
	{
		m_pCurrentShape->setLineColor(lineColor);
		update();
		saveState();//保存当前状态
	}
}
void KCanvas::onLineStyleHandle(int index)
{
	if (m_pCurrentShape)
	{
		if (index == 0)
		{
			m_pCurrentShape->setLineStyle(Qt::SolidLine);
			update();
		}
		else if (index == 1)
		{
			m_pCurrentShape->setLineStyle(Qt::DashLine);
			update();
		}
		else if (index == 2)
		{
			m_pCurrentShape->setLineStyle(Qt::DotLine);
			update();
		}
		saveState();//保存当前状态

	}
}
void KCanvas::onScaleShapeChanged(double scale)
{
	for (auto shape : m_pShapeList)
	{
		shape->setScale(scale);
		update();
		saveState();//保存当前状态
	}
}


// 绘图事件处理
void KCanvas::paintEvent(QPaintEvent * event)
{
#if 0
	if (!m_pShapeList->isEmpty())
	{
		//遍历图形对象的  List
		for (QList<KShape*>::iterator it = m_pShapeList->begin();
			it != m_pShapeList->end(); ++it)
			(*it)->drawShape(this);// 绘制
	}
#endif

	//为了打开本地svg
	QPainter painter(this);
	// 如果已加载SVG文件，则绘制SVG图像
	if (m_svgRenderer && m_svgRenderer->isValid()) {
		m_svgRenderer->render(&painter); // 使用QPainter绘制SVG
	}
	//为了打开本地svg

	// 遍历形状列表并绘制
	for (KShape* shape : m_pShapeList)
	{
		//shape->drawShape(this);

		// 如果全选了，绘制外边框
		if (m_isAllSelected)
		{
			shape->drawOutLine(this);
		}
	}

	if (!m_pShapeList.isEmpty())
	{
		auto it = m_pShapeList.rbegin();
		while (it != m_pShapeList.rend())
		{
			(*it)->drawShape(this);//这里就响应每次拉动矩形边框来调整内部图形的大小
			it++;
		}
	}

	if (m_pCurrentShape != Q_NULLPTR)
	{
		if (m_isDrawing) // 图形绘制标志为 true，则表示正在绘制该图形，此时需要不断重新绘制
			m_pCurrentShape->drawShape(this);  //这里调用的是shape各子类的绘画函数

		if (m_isSelected) // 就是那个鼠标的功能被选择了，会把m_isSelected置为true，图形选中，则绘制选中框，就是矩形框
			m_pCurrentShape->drawOutLine(this);  //这是绘制矩形框的，任何图形都是基于矩形框来绘制的，利用起始点和终点来绘制
	}
}

void KCanvas::mousePressEvent(QMouseEvent * event)
{
	m_pCurrentShape = getCurrentShape(changingWithScale(event->pos()));
	if (event->button() == Qt::LeftButton)
	{
		if (!m_pCurrentShape)
		{
			m_isAllSelected = false;
			update();
		}//取消全选
	}



	


	//judge right press show menu
	//judge all windows
	if (event->button() == Qt::RightButton)
	{
		// 右键菜单弹出前，根据当前图形是否选中，设置标志位
		//m_isShapeSelected = (getCurrentShape(changingWithScale(event->pos())) != nullptr);
		if (m_isSelected)
		{
			m_isShapeSelected = true;
		}
		else
		{
			m_isShapeSelected = false;
		}

		// 弹出右键菜单
		m_rightMenu = new KRightMenu(m_isShapeSelected, this);
		initConnet();//为了使得右键新建对象后链接仍然有效
		m_rightMenu->exec(event->globalPos());
		return;
	}

	//获取当前需要绘制的图形类型
	KGlobalData::KDrawFlag flag = KGlobalData::getGlobalDataIntance()->getDrawFlag();

	if (flag == KGlobalData::KDrawFlag::NoneDrawFlag)
		return;

	// 检查是否处于全选状态和点击的位置是否有图像
	if (m_isAllSelected && event->buttons() == Qt::LeftButton && m_pCurrentShape)
	{
		m_lastPos = changingWithScale(event->pos());
	}
	else if (event->buttons() == Qt::LeftButton)
	{
		m_isLPress = true;// 记录鼠标左键已经点击
		if (flag == KGlobalData::KDrawFlag::MouseDrawFlag)
		{
			//saveState();//为了移动后undo回去
			m_pCurrentShape = getCurrentShape(changingWithScale(event->pos()));

			if (m_pCurrentShape != Q_NULLPTR)
			{
				m_lastPos = changingWithScale(event->pos());// 当前位置移动的最后位置(会更新)
				m_isSelected = true;// 设置选中标志
				m_TransType = getTransType(changingWithScale(event->pos()));// 获取移动类型

				//m_isShapeSelected = true; // 设置图形已选中,判断右键

				
			}
			else
			{
				m_isSelected = false;
				//m_isShapeSelected = false;//未选中的右键 
			}
		}
		else if (flag == KGlobalData::KDrawFlag::PenDrawFlag)
		{

			m_isSelected = false;
			m_pCurrentShape = KShapeFactory::createShape(KGlobalData::getGlobalDataIntance()->getDrawFlag());
			if (m_pCurrentShape != Q_NULLPTR)
				static_cast<KPen*> (m_pCurrentShape)->addPos(changingWithScale(event->pos()));

		}
		else if (flag == KGlobalData::KDrawFlag::CircleDrawFlag) // 圆形绘制
		{
			m_isSelected = false;
			m_pCurrentShape = KShapeFactory::createShape(KGlobalData::getGlobalDataIntance()->getDrawFlag());

			if (m_pCurrentShape != Q_NULLPTR)
				static_cast<KCircle*>(m_pCurrentShape)->setStartPoint(changingWithScale(event->pos()));
		}
		else if (flag == KGlobalData::KDrawFlag::LineDrawFlag) // 直线绘制
		{
			m_isSelected = false;
			m_pCurrentShape = KShapeFactory::createShape(KGlobalData::getGlobalDataIntance()->getDrawFlag());

			if (m_pCurrentShape != Q_NULLPTR)
				static_cast<KLine*> (m_pCurrentShape)->setStartPoint(changingWithScale(event->pos()));//设置起始点
		}
		else if (flag == KGlobalData::KDrawFlag::TextDrawFlag) // 输入的文本
		{
			m_isSelected = false;
			m_pCurrentShape = KShapeFactory::createShape(KGlobalData::getGlobalDataIntance()->getDrawFlag());
			if (m_pCurrentShape != Q_NULLPTR)
			{
				static_cast<KText*>(m_pCurrentShape)->setStartPoint(changingWithScale(event->pos()));
				static_cast<KText*>(m_pCurrentShape)->showTextBox(this);
				m_pShapeList.prepend(m_pCurrentShape);
				m_pCurrentShape = Q_NULLPTR;
			
			}
		}
		else if (flag == KGlobalData::KDrawFlag::FiveDrawFlag) // 五边形绘制
		{
			m_isSelected = false;
			m_pCurrentShape = KShapeFactory::createShape(KGlobalData::getGlobalDataIntance()->getDrawFlag());

			if (m_pCurrentShape != Q_NULLPTR)
				static_cast<KFive*>(m_pCurrentShape)->setStartPoint(changingWithScale(event->pos()));
		}
		else if (flag == KGlobalData::KDrawFlag::SixDrawFlag) // 6边形绘制
		{
			m_isSelected = false;
			m_pCurrentShape = KShapeFactory::createShape(KGlobalData::getGlobalDataIntance()->getDrawFlag());

			if (m_pCurrentShape != Q_NULLPTR)
				static_cast<KSix*>(m_pCurrentShape)->setStartPoint(changingWithScale(event->pos()));
			
		}
		else if (flag == KGlobalData::KDrawFlag::StarDrawFlag) //五角星
		{
			m_isSelected = false;
			m_pCurrentShape = KShapeFactory::createShape(KGlobalData::getGlobalDataIntance()->getDrawFlag());

			if (m_pCurrentShape != Q_NULLPTR)
				static_cast<KStar*>(m_pCurrentShape)->setStartPoint(changingWithScale(event->pos()));
			
		}
		else
		{
			m_isSelected = false;
			m_pCurrentShape = KShapeFactory::createShape(KGlobalData::getGlobalDataIntance()->getDrawFlag());

			if (m_pCurrentShape != Q_NULLPTR)
				m_pCurrentShape->setStartPoint(changingWithScale(event->pos()));
			//saveState();//保存当前状态
		}

	}
	update();

}

void KCanvas::mouseMoveEvent(QMouseEvent * event)
{
	KGlobalData::KDrawFlag flag = KGlobalData::getGlobalDataIntance()->getDrawFlag();
	if (flag == KGlobalData::KDrawFlag::NoneDrawFlag)
		return;


	KTransType transType = getTransType(changingWithScale(event->pos()));
	updateCusorStyle(flag, transType);//选中时设置鼠标选中样式

	if (event->buttons() != Qt::LeftButton)//bug : 在不点击鼠标左键并在在选中状态，移动鼠标会移动图形
		return;


	if (flag != KGlobalData::KDrawFlag::MouseDrawFlag)
	{
		if (flag == KGlobalData::KDrawFlag::PenDrawFlag)
		{
			if (m_isLPress && !m_isDrawing)
				m_isDrawing = true;
			if (m_pCurrentShape != Q_NULLPTR)
				qobject_cast<KPen*>(m_pCurrentShape)->addPos(changingWithScale(event->pos()));
		}
		else if (flag == KGlobalData::KDrawFlag::CircleDrawFlag) // 圆形绘制
		{
			if (m_isLPress && !m_isDrawing)
				m_isDrawing = true;
			if (m_pCurrentShape != Q_NULLPTR)
				qobject_cast<KCircle*>(m_pCurrentShape)->setEndPoint(changingWithScale(event->pos()));
		}
		else if (flag == KGlobalData::KDrawFlag::LineDrawFlag) // 直线绘制
		{
			if (m_isLPress && !m_isDrawing)
				m_isDrawing = true;
			if (m_pCurrentShape != Q_NULLPTR)
				qobject_cast<KLine*>(m_pCurrentShape)->setEndPoint(changingWithScale(event->pos()));
		}
		else if (flag == KGlobalData::KDrawFlag::TextDrawFlag) // 文本
		{
			//

		}
		else if (flag == KGlobalData::KDrawFlag::FiveDrawFlag) // 五边形绘制
		{
			if (m_isLPress && !m_isDrawing)
				m_isDrawing = true;
			if (m_pCurrentShape != Q_NULLPTR)
				qobject_cast<KFive*>(m_pCurrentShape)->setEndPoint(changingWithScale(event->pos()));
		}
		else if (flag == KGlobalData::KDrawFlag::SixDrawFlag) // 6边形绘制
		{
			if (m_isLPress && !m_isDrawing)
				m_isDrawing = true;
			if (m_pCurrentShape != Q_NULLPTR)
				qobject_cast<KSix*>(m_pCurrentShape)->setEndPoint(changingWithScale(event->pos()));
		}
		else if (flag == KGlobalData::KDrawFlag::StarDrawFlag) // 五角星绘制
		{
			if (m_isLPress && !m_isDrawing)
				m_isDrawing = true;
			if (m_pCurrentShape != Q_NULLPTR)
				qobject_cast<KStar*>(m_pCurrentShape)->setEndPoint(changingWithScale(event->pos()));
		}
		else
		{

			if (m_isLPress && !m_isDrawing)
				m_isDrawing = true;
			if (m_pCurrentShape != Q_NULLPTR)
				m_pCurrentShape->setEndPoint(changingWithScale(event->pos()));
				
		}
	}
	else
	{
		if (m_isAllSelected && event->buttons() == Qt::LeftButton)
		{
			// 计算鼠标移动的偏移量
			QPoint offset = changingWithScale(event->pos()) - m_lastPos;
			m_lastPos = changingWithScale(event->pos());

			// 移动所有图形
			for (auto& shape : m_pShapeList)
			{
				shape->move(offset);
			}
		}
		else
		{
			if (m_pCurrentShape == Q_NULLPTR)
				return;
			dragMoveShape(transType, changingWithScale(event->pos()));//移动选中图形
		}
		
	}

	update();//这里会不断在移动过程当中绘画，调用的是paintevent函数，在这里重写了，在上面

}

void KCanvas::mouseReleaseEvent(QMouseEvent * event)
{
	KGlobalData::KDrawFlag flag = KGlobalData::getGlobalDataIntance()->getDrawFlag();

	if (m_isLPress) // 鼠标左键按下后释放，则表示移动或者绘图完毕
	{
		
		if (flag != KGlobalData::KDrawFlag::MouseDrawFlag)// 如果是绘图
		{

			if (flag == KGlobalData::KDrawFlag::PenDrawFlag)
			{
				qobject_cast<KPen*>(m_pCurrentShape)->addPos(changingWithScale(event->pos()));
				qobject_cast<KPen*>(m_pCurrentShape)->setStartPoint();
				qobject_cast<KPen*>(m_pCurrentShape)->setEndPoint();

			}

			else if (flag == KGlobalData::KDrawFlag::CircleDrawFlag) // 圆形绘制
				qobject_cast<KCircle*>(m_pCurrentShape)->setEndPoint(changingWithScale(event->pos()));
			else if (flag == KGlobalData::KDrawFlag::LineDrawFlag) // 直线绘制
				qobject_cast<KLine*>(m_pCurrentShape)->setEndPoint(changingWithScale(event->pos()));
			else if (flag == KGlobalData::KDrawFlag::TextDrawFlag) // 文本释放处理
			{
				//
			}
			else if (flag == KGlobalData::KDrawFlag::FiveDrawFlag) // 五边形绘制
				qobject_cast<KFive*>(m_pCurrentShape)->setEndPoint(changingWithScale(event->pos()));
			else if (flag == KGlobalData::KDrawFlag::FiveDrawFlag) // 6边形绘制
				qobject_cast<KFive*>(m_pCurrentShape)->setEndPoint(changingWithScale(event->pos()));
			else if (flag == KGlobalData::KDrawFlag::StarDrawFlag) // 五角星
				qobject_cast<KStar*>(m_pCurrentShape)->setEndPoint(changingWithScale(event->pos()));


			//这里加上一个pen的限制是为了使上面的setEndPoint生效，绘制一个更大一些的矩形边框
			if (flag != KGlobalData::KDrawFlag::TextDrawFlag && flag != KGlobalData::KDrawFlag::PenDrawFlag)//因为文本呢不需要设置这个终点，所以为了防止报错，这里就加一个条件
				m_pCurrentShape->setEndPoint(changingWithScale(event->pos()));

			if (m_pCurrentShape != Q_NULLPTR)
			{
				if (m_pCurrentShape->isValid())
				{	
					saveState();
					m_pShapeList.prepend(m_pCurrentShape);
					//saveState();
					m_pCurrentShape = Q_NULLPTR;
					m_isSelected = true;
					m_isDrawing = false;
					
				}
			}
			else
			{
				
				delete m_pCurrentShape;
				m_pCurrentShape = Q_NULLPTR;
				//saveState();//为了移动能undo直接回去
			}
			
		}
	/*	else
		{
			m_pCurrentShape = getCurrentShape(changingWithScale(event->pos()));
			if (flag == KGlobalData::KDrawFlag::MouseDrawFlag && m_pCurrentShape && m_isSelected)
			{
				saveState();
			}

		}*/
		


		m_isLPress = false;
		m_isDrawing = false;
		m_TransType = KTransType::None;
	}

	update();
	//saveState();//保存当前状态
}

KShape* KCanvas::getCurrentShape(const QPoint & pos)
{
	
	(QPoint)pos = changingWithScale(pos);
	
	//(QPoint)pos = changingWithScale(pos);
	for (QList<KShape*>::iterator it = m_pShapeList.begin();
		it != m_pShapeList.end(); ++it)
	{
		if ((*it)->getShapeRect().contains(pos))
			return *it;
	}

	return Q_NULLPTR;
}

KTransType KCanvas::getTransType(const QPoint & pos)
{
	(QPoint)pos = changingWithScale(pos);
	if (!m_pCurrentShape)
		return KTransType::None;

	// 获取图形矩形
	QRect rect = m_pCurrentShape->getShapeRect();

	if (!rect.contains(pos))
		return KTransType::None;

	/*qDebug() << "rect = " << rect.topLeft().x();
	qDebug() << "rect = " << rect.topLeft().y();*/

	// 判断是整体移动，局部拖拽移动
	if (qAbs(pos.x() - rect.topLeft().x()) < 5
		&& qAbs(pos.y() - rect.topLeft().y()) < 5)
		return KTransType::TopLeft;

	if (qAbs(rect.topRight().x() - pos.x()) < 5
		&& qAbs(pos.y() - rect.topRight().y()) < 5)
		return KTransType::TopRight;

	if (qAbs(rect.bottomRight().x() - pos.x()) < 5
		&& qAbs(rect.bottomRight().y() - pos.y()) < 5)
		return KTransType::BottomRight;

	if (qAbs(pos.x() - rect.bottomLeft().x()) < 5
		&& qAbs(rect.bottomLeft().y() - pos.y()) < 5)
		return KTransType::BottomLeft;

	if (qAbs(pos.y() - rect.top()) < 5
		&& pos.x() > rect.topLeft().x() + 5
		&& pos.x() < rect.topRight().x() - 5)
		return KTransType::Top;

	if (qAbs(rect.right() - pos.x()) < 5
		&& pos.y() > rect.topRight().y() + 5
		&& pos.y() < rect.bottomRight().y() - 5)
		return KTransType::Right;

	if (qAbs(rect.bottom() - pos.y()) < 5
		&& pos.x() > rect.bottomLeft().x() + 5
		&& pos.x() < rect.bottomRight().x() - 5)
		return KTransType::Bottom;

	if (qAbs(pos.x() - rect.left()) < 5
		&& pos.y() > rect.topLeft().y() + 5
		&& pos.y() < rect.bottomLeft().y() - 5)
		return KTransType::Left;

	return KTransType::Contains;
}

void KCanvas::updateCusorStyle(KGlobalData::KDrawFlag flag, KTransType transType)
{
	// 如果已经选中
	if (m_isSelected
		&& flag == KGlobalData::KDrawFlag::MouseDrawFlag
		&& transType != KTransType::None)
	{
		//TODO：变换图标,设置不同的鼠标样式,根据点击位置，设置不同的鼠标样式
		if (transType == KTransType::TopLeft || transType == KTransType::BottomRight)
			setCursor(Qt::SizeFDiagCursor);
		else if (transType == KTransType::TopRight || transType == KTransType::BottomLeft)
			setCursor(Qt::SizeBDiagCursor);
		else if (transType == KTransType::Top || transType == KTransType::Bottom)
			setCursor(Qt::SizeVerCursor);
		else if (transType == KTransType::Left || transType == KTransType::Right)
			setCursor(Qt::SizeHorCursor);

		else if (transType == KTransType::Contains)
			setCursor(Qt::SizeAllCursor);
	}
	else
		unsetCursor();
}

void KCanvas::dragMoveShape(KTransType transType, const QPoint & pos)
{


	if (m_pCurrentShape == NULL)
		return;

	/*
		在移动过程中，分为两种移动方式
			(1) 整体移动  contains
			(2) 基于某一个方向的拖拽移动

	*/
	switch (m_TransType)
	{
		
	case KTransType::None:
		return;
	case KTransType::TopLeft:
		// 如果是左上角，则当前位置为新的矩形起始位置
		m_pCurrentShape->moveTopLeft(pos);
		break;
	case KTransType::Top:
		// 如果是向上移动，则修改起始位置的 y 坐标
		m_pCurrentShape->moveTop(pos);
		break;
	case KTransType::TopRight:
		m_pCurrentShape->moveTopRight(pos);
		break;
	case KTransType::Left:
		m_pCurrentShape->moveLeft(pos);
		break;
	case KTransType::Contains: // 整体移动
	{
		// m_lastPos 为选中时光标位置，在移动过程中不断赋值为前一次的位置
		QPoint newpos = pos - m_lastPos; // 计算要移动的偏移
		m_pCurrentShape->move(newpos);
		m_lastPos = pos;
	}
	break;
	case KTransType::Right:
		m_pCurrentShape->moveRight(pos);
		break;
	case KTransType::BottomLeft:
		m_pCurrentShape->moveBottomLeft(pos);
		break;
	case KTransType::Bottom:
		m_pCurrentShape->moveBottom(pos);
		break;
	case KTransType::BottomRight:
		m_pCurrentShape->moveBottomRight(pos);
		break;
	default:
		break;
	}
//	saveState();  // 保存当前状态
}
QPoint KCanvas::changingWithScale(const QPoint& pos)
{
	// 获取缩放比例，确保是浮点数
	double scale = KGlobalData::getGlobalDataIntance()->getCanvasScale();
	return pos / scale;
	// 返回缩放后的QPoint，使用浮点数进行计算并转回QPoint
	//return QPoint(static_cast<int>(pos.x() / scale), static_cast<int>(pos.y() / scale));
}


void KCanvas::clearAllShape()
{
	

	// 检查当前选中的形状是否在清空列表中
	if (m_pShapeList.contains(m_pCurrentShape)) 
	{
		m_pCurrentShape = nullptr; // 清空指向已删除对象的指针
	}

	// 遍历形状列表，删除所有形状
	for (auto& shape : m_pShapeList) 
	{
		delete shape;
	}
	m_pShapeList.clear(); // 清空列表
	m_isSelected = false; // 取消选中状态



	 // 清除SVG图像
	if (m_svgRenderer != nullptr) 
	{
		delete m_svgRenderer;
		m_svgRenderer = nullptr; // 重置指针
	}


	update(); // 更新画布
}
void KCanvas::saveToSvg()
{
	// 弹出文件对话框，获取保存路径
	QString filePath = QFileDialog::getSaveFileName(this, tr("Save SVG File"), "", tr("SVG Files (*.svg)"));

	// 取消了保存操作，则直接返回
	if (filePath.isEmpty())
	{
		return;
	}

	QSvgGenerator generator;
	generator.setFileName(filePath);
	generator.setSize(this->size());
	generator.setViewBox(QRect(0, 0, width(), height()));

	
		// 创建 QPainter 对象并绑定到 QSvgGenerator 上
	QPainter painter(&generator);

	// 调用绘制函数，将 QPainter 对象传递进去
	for (const auto& shape : m_pShapeList)
	{
		if (shape)
		{
			shape->drawShape(&painter); // 使用 QPainter 对象绘制
		}
	}

	painter.end(); // 结束绘制

	qDebug() << "SVG saved to:" << filePath;
}
void KCanvas::openSvg()
{
	// 打开文件对话框选择SVG文件
	QString filePath = QFileDialog::getOpenFileName(this, tr("Open SVG File"), "", tr("SVG Files (*.svg)"));
	if (filePath.isEmpty()) 
	{
		return; // 取消选择，直接返回
	}	
	//这里确保打开的时候画面干净、清楚点之前画的
	// 删除之前加载的 SVG 渲染器--二版本
	if (m_svgRenderer != nullptr)
	{
		delete m_svgRenderer;
		m_svgRenderer = nullptr;
	}
	//这里确保打开的时候画面干净、清楚点之前画的
	// 检查当前选中的形状是否在清空列表中
	if (m_pShapeList.contains(m_pCurrentShape))
	{
		m_pCurrentShape = nullptr; // 清空指向已删除对象的指针
	}

	// 遍历形状列表，删除所有形状
	for (auto& shape : m_pShapeList)
	{
		delete shape;
	}
	m_pShapeList.clear(); // 清空列表
	m_isSelected = false; // 取消选中状态
	// 创建新的 SVG 文件
	m_svgRenderer = new QSvgRenderer(filePath, this);

	if (!m_svgRenderer->isValid()) 
	{
		qDebug() << "Failed to load SVG file:" << filePath;
		delete m_svgRenderer;
		m_svgRenderer = nullptr;
		return;
	}
	update(); // 重绘显示加载的SVG图像

}
void KCanvas::exportToPng()
{
	// 设置保存的PNG文件路径
	QString filePath = QFileDialog::getSaveFileName(this, tr("Save PNG File"), "", tr("PNG Files (*.png)"));
	if (filePath.isEmpty())
	{
		return; // 取消保存操作，则直接返回
	}
	
	// 创建 QImage 对象，大小与当前画布一致
	QImage image(this->size(), QImage::Format_ARGB32);
	image.fill(Qt::transparent); // 将背景设置为透明

	// 使用 QPainter 绘制到 QImage 上
	QPainter painter(&image);
	this->render(&painter); // 将当前的画布内容渲染到 QImage 上

	// 保存 QImage 为 PNG 文件
	if (!image.save(filePath))
	{
		qDebug() << "Failed to save PNG file:" << filePath;
	}
	else
	{
		qDebug() << "PNG saved to:" << filePath;
	}
}
