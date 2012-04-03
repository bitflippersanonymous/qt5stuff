/********************************************************************************
** Form generated from reading UI file 'qt5stuff.ui'
**
** Created: Mon Apr 2 23:56:46 2012
**      by: Qt User Interface Compiler version 5.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT5STUFF_H
#define UI_QT5STUFF_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qt5stuffClass
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *qt5stuffClass)
    {
        if (qt5stuffClass->objectName().isEmpty())
            qt5stuffClass->setObjectName(QStringLiteral("qt5stuffClass"));
        qt5stuffClass->resize(800, 600);
        centralwidget = new QWidget(qt5stuffClass);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        qt5stuffClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(qt5stuffClass);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        qt5stuffClass->setMenuBar(menubar);
        statusbar = new QStatusBar(qt5stuffClass);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        qt5stuffClass->setStatusBar(statusbar);

        retranslateUi(qt5stuffClass);

        QMetaObject::connectSlotsByName(qt5stuffClass);
    } // setupUi

    void retranslateUi(QMainWindow *qt5stuffClass)
    {
        qt5stuffClass->setWindowTitle(QApplication::translate("qt5stuffClass", "MainWindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class qt5stuffClass: public Ui_qt5stuffClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT5STUFF_H
