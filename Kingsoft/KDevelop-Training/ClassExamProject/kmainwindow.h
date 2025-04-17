#ifndef __K_MAINWINDOW_H_
#define __K_MAINWINDOW_H_

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QCloseEvent>
#include "kmdiarea.h"
#include "ktoolbar.h"
#include "ksvgmainwindow.h"
#include "kcanvasparamsbar.h"
#include "kfilemenu.h"
#include "kbatchprocessdialog.h"
#include "ui_kmainwindow.h"

class KMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    KMainWindow(QWidget *parent = Q_NULLPTR);
    ~KMainWindow();
   
    void initWindows();
    void initMenus();
    void initToolbars();
    void initConnections();
    void initSettings();
    
    void saveSettings();
    void loadSettings();

    bool openSVGFile(const QString& filePath);
    bool saveCurrentSVGFile(const QString& filePath);

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void createNewDocument();
    void openSVGDocument();
    void saveCurrentDocument();
    void saveAsCurrentDocument();
    void exportCurrentToPNG();
    void showBatchProcessDialog();
    void onActiveWindowChanged(QMdiSubWindow* window);
    void onDocumentModified();
    void updateWindowTitle();
    void updateMenus();
    void updateStatusBar();
    
    // 窗口管理
    void tileSubWindows();
    void cascadeSubWindows();
    void closeActiveWindow();
    void closeAllWindows();
    
private:
    KSvgMainWindow* activeEditor();
    
    Ui::KMainWindowClass ui;
    KMdiArea* m_pMdiArea;
    KToolBar* m_pToolBar;
    KCanvasParamsBar* m_pCanvasParamsBar;
    
    QMenu* m_pFileMenu;
    QMenu* m_pEditMenu;
    QMenu* m_pViewMenu;
    QMenu* m_pWindowMenu;
    QMenu* m_pHelpMenu;
    
    // 文件菜单动作
    QAction* m_pNewAction;
    QAction* m_pOpenAction;
    QAction* m_pSaveAction;
    QAction* m_pSaveAsAction;
    QAction* m_pExportPngAction;
    QAction* m_pBatchProcessAction;
    QAction* m_pExitAction;
    
    // 编辑菜单动作
    QAction* m_pUndoAction;
    QAction* m_pRedoAction;
    QAction* m_pCutAction;
    QAction* m_pCopyAction;
    QAction* m_pPasteAction;
    QAction* m_pSelectAllAction;
    
    // 视图菜单动作
    QAction* m_pZoomInAction;
    QAction* m_pZoomOutAction;
    QAction* m_pZoomResetAction;
    
    // 窗口菜单动作
    QAction* m_pTileAction;
    QAction* m_pCascadeAction;
    QAction* m_pCloseWindowAction;
    QAction* m_pCloseAllAction;
    
    // 帮助菜单动作
    QAction* m_pAboutAction;
    
    KBatchProcessDialog* m_pBatchDialog;
};

#endif
