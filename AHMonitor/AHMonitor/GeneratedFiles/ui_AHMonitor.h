/********************************************************************************
** Form generated from reading UI file 'AHMonitor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AHMONITOR_H
#define UI_AHMONITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AHMonitorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AHMonitorClass)
    {
        if (AHMonitorClass->objectName().isEmpty())
            AHMonitorClass->setObjectName(QStringLiteral("AHMonitorClass"));
        AHMonitorClass->resize(600, 400);
        menuBar = new QMenuBar(AHMonitorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        AHMonitorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AHMonitorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        AHMonitorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(AHMonitorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        AHMonitorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(AHMonitorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        AHMonitorClass->setStatusBar(statusBar);

        retranslateUi(AHMonitorClass);

        QMetaObject::connectSlotsByName(AHMonitorClass);
    } // setupUi

    void retranslateUi(QMainWindow *AHMonitorClass)
    {
        AHMonitorClass->setWindowTitle(QApplication::translate("AHMonitorClass", "AHMonitor", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AHMonitorClass: public Ui_AHMonitorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AHMONITOR_H
