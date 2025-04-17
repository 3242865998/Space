/********************************************************************************
** Form generated from reading UI file 'kmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KMAINWINDOW_H
#define UI_KMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KMainWindowClass
{
public:

    void setupUi(QWidget *KMainWindowClass)
    {
        if (KMainWindowClass->objectName().isEmpty())
            KMainWindowClass->setObjectName(QString::fromUtf8("KMainWindowClass"));
        KMainWindowClass->resize(600, 400);
        KMainWindowClass->setMouseTracking(false);
        KMainWindowClass->setStyleSheet(QString::fromUtf8("background-color:#2f2f2c;"));

        retranslateUi(KMainWindowClass);

        QMetaObject::connectSlotsByName(KMainWindowClass);
    } // setupUi

    void retranslateUi(QWidget *KMainWindowClass)
    {
        KMainWindowClass->setWindowTitle(QCoreApplication::translate("KMainWindowClass", "KMainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KMainWindowClass: public Ui_KMainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KMAINWINDOW_H
