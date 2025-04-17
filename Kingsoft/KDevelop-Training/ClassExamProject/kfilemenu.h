#ifndef KFILEMENU_H
#define KFILEMENU_H

#include <QMenuBar>

class KMainWindow;  // Ç°ÏòÉùÃ÷

class KFileMenu : public QMenuBar
{
	Q_OBJECT

public:
	explicit KFileMenu(KMainWindow* mainWindow, QWidget* parent = nullptr);

private slots:
	void newFile();
	void openSVG();
	void save();
	void exportPNG();

private:
	KMainWindow* m_mainWindow;
};

#endif // KFILEMENU_H
