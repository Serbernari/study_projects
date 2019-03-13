/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myGlWidger
{
public:
    QWidget *centralWidget;
    QSlider *xRotSlider;
    QSlider *yRotSlider;
    QSlider *zRotSlider;
    QOpenGLWidget *openGLWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *myGlWidger)
    {
        if (myGlWidger->objectName().isEmpty())
            myGlWidger->setObjectName(QString::fromUtf8("myGlWidger"));
        myGlWidger->resize(400, 452);
        centralWidget = new QWidget(myGlWidger);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        xRotSlider = new QSlider(centralWidget);
        xRotSlider->setObjectName(QString::fromUtf8("xRotSlider"));
        xRotSlider->setGeometry(QRect(110, 240, 160, 16));
        xRotSlider->setMaximum(360);
        xRotSlider->setSingleStep(16);
        xRotSlider->setPageStep(14);
        xRotSlider->setOrientation(Qt::Horizontal);
        xRotSlider->setTickPosition(QSlider::TicksAbove);
        xRotSlider->setTickInterval(15);
        yRotSlider = new QSlider(centralWidget);
        yRotSlider->setObjectName(QString::fromUtf8("yRotSlider"));
        yRotSlider->setGeometry(QRect(110, 290, 160, 16));
        yRotSlider->setMaximum(360);
        yRotSlider->setSingleStep(16);
        yRotSlider->setPageStep(14);
        yRotSlider->setOrientation(Qt::Horizontal);
        yRotSlider->setTickPosition(QSlider::TicksAbove);
        yRotSlider->setTickInterval(15);
        zRotSlider = new QSlider(centralWidget);
        zRotSlider->setObjectName(QString::fromUtf8("zRotSlider"));
        zRotSlider->setGeometry(QRect(110, 330, 160, 16));
        zRotSlider->setMaximum(360);
        zRotSlider->setSingleStep(16);
        zRotSlider->setPageStep(14);
        zRotSlider->setOrientation(Qt::Horizontal);
        zRotSlider->setTickPosition(QSlider::TicksAbove);
        zRotSlider->setTickInterval(15);
        openGLWidget = new QOpenGLWidget(centralWidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(50, 20, 300, 200));
        myGlWidger->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(myGlWidger);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 20));
        myGlWidger->setMenuBar(menuBar);
        mainToolBar = new QToolBar(myGlWidger);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        myGlWidger->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(myGlWidger);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        myGlWidger->setStatusBar(statusBar);

        retranslateUi(myGlWidger);

        QMetaObject::connectSlotsByName(myGlWidger);
    } // setupUi

    void retranslateUi(QMainWindow *myGlWidger)
    {
        myGlWidger->setWindowTitle(QApplication::translate("myGlWidger", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myGlWidger: public Ui_myGlWidger {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
