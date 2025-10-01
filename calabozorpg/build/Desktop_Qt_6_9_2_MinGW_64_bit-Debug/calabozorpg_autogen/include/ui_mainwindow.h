/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QGraphicsView *mapaCalabozo;
    QFrame *frame_2;
    QProgressBar *barraVida;
    QPushButton *btnAtacar;
    QPushButton *btnLanzarDados;
    QLabel *lblVida;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setMouseTracking(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        mapaCalabozo = new QGraphicsView(frame);
        mapaCalabozo->setObjectName("mapaCalabozo");
        mapaCalabozo->setGeometry(QRect(60, 130, 171, 111));

        horizontalLayout->addWidget(frame);

        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        barraVida = new QProgressBar(frame_2);
        barraVida->setObjectName("barraVida");
        barraVida->setGeometry(QRect(180, 160, 118, 23));
        barraVida->setMouseTracking(true);
        barraVida->setValue(24);
        btnAtacar = new QPushButton(frame_2);
        btnAtacar->setObjectName("btnAtacar");
        btnAtacar->setGeometry(QRect(40, 40, 90, 29));
        btnLanzarDados = new QPushButton(frame_2);
        btnLanzarDados->setObjectName("btnLanzarDados");
        btnLanzarDados->setGeometry(QRect(130, 330, 90, 29));
        lblVida = new QLabel(frame_2);
        lblVida->setObjectName("lblVida");
        lblVida->setGeometry(QRect(250, 370, 63, 20));
        lblVida->setMouseTracking(true);

        horizontalLayout->addWidget(frame_2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnAtacar->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        btnLanzarDados->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        lblVida->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
